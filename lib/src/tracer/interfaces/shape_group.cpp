//
// Created by iliya on 5/2/26.
//

#include "shape_group.h"
#include <algorithm>
#include <stack>

// Простая функция для вычисления центроида AABB
static inline float centroid(const AABB& box, int axis) {
    if (axis == 0) return (box.min + box.max).getX() * 0.5f;
    if (axis == 1) return (box.min + box.max).getY() * 0.5f;
    return (box.min + box.max).getZ() * 0.5f;
}

// Построение дерева
std::unique_ptr<IShapesGroup::BVHNode> IShapesGroup::BVHNode::build(std::vector<const IShape*>& shapes, int begin, int end) noexcept {
    if (begin >= end) return nullptr;

    auto node = std::make_unique<IShapesGroup::BVHNode>();

    // Вычисляем общий AABB
    AABB bounds = shapes[begin]->getBoundingBox();
    for (int i = begin + 1; i < end; ++i) {
        AABB b = shapes[i]->getBoundingBox();
        bounds.min = (bounds.min < b.min).combine(bounds.min, b.min);
        bounds.max = (bounds.max > b.max).combine(bounds.max, b.max);
    }
    node->box = bounds;

    int count = end - begin;
    if (count == 1) {
        node->shape = shapes[begin];
        return node;
    }

    // Ищем ось с наибольшей протяжённостью
    Vector3d diag = bounds.max - bounds.min;
    int axis = 0;
    if (diag.getY() > diag.getX()) axis = 1;
    if (diag.getZ() > ((axis == 0) ? diag.getX() : diag.getY())) axis = 2;

    // Сортируем по центроиду по выбранной оси
    auto beginIt = shapes.begin() + begin;
    auto endIt   = shapes.begin() + end;
    std::nth_element(beginIt, beginIt + count / 2, endIt,
                     [axis](const IShape* a, const IShape* b) {
                         return centroid(a->getBoundingBox(), axis) <
                                centroid(b->getBoundingBox(), axis);
                     });

    int mid = begin + count / 2;
    node->left  = build(shapes, begin, mid);
    node->right = build(shapes, mid, end);
    return node;
}


void IShapesGroup::buildBVH() {
    if (shapes.empty()) return;

    // Работаем с копией вектора указателей
    std::vector<const IShape*> work(shapes);
    root = BVHNode::build(work, 0, work.size());
    bvhBuilt = true;
}

// Обход дерева со стеком
bool IShapesGroup::traverse(const BVHNode* node, const Ray& ray, float t_min, float t_max, HitRecord& hit) const noexcept {
    if (!node) return false;
    if (!node->box.hit(ray, t_min, t_max)) return false;

    // Лист
    if (node->shape) {
        HitRecord temp;
        if (node->shape->intersect(ray, t_min, t_max, temp)) {
            hit = temp;
            return true;
        }
        return false;
    }

    bool hit_left = traverse(node->left.get(), ray, t_min, t_max, hit);

    float new_t_max = hit_left ? hit.t : t_max;
    bool hit_right = traverse(node->right.get(), ray, t_min, new_t_max, hit);
    return hit_left || hit_right;
}

bool IShapesGroup::intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const noexcept {
    if (bvhBuilt && root) {
        return traverse(root.get(), ray, t_min, t_max, hit);
    }
    // Полный перебор
    HitRecord temp;
    bool hit_anything = false;
    float closest = t_max;
    for (auto shape : shapes) {
        if (shape->intersect(ray, t_min, closest, temp)) {
            hit_anything = true;
            closest = temp.t;
            hit = temp;
        }
    }
    return hit_anything;
}
