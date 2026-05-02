//
// Created by iliya on 5/2/26.
//

#ifndef TRACER_INTERFACES_SHAPE_GROUP_H
#define TRACER_INTERFACES_SHAPE_GROUP_H

#include <vector>
#include <memory>
#include "shape.h"
#include "tracer/structs.h"

// TODO - сделать c_api
class IShapesGroup : public IShape {
    struct BVHNode {
        AABB box;
        std::unique_ptr<BVHNode> left;
        std::unique_ptr<BVHNode> right;
        // Только для листьев
        const IShape* shape = nullptr;

        // Функция построения дерева
        static std::unique_ptr<BVHNode> build(std::vector<const IShape*>& shapes, int begin, int end) noexcept;
    };
public:
    void add(const IShape* shape) noexcept {
        shapes.push_back(shape);
        bvhBuilt = false;
    }

    const std::vector<const IShape*>& getShapes() const noexcept {
        return shapes;
    }

    // Принудительно построить BVH
    void buildBVH();

    bool intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const noexcept override;

    inline AABB getBoundingBox() const noexcept override {
        if (shapes.empty()) return {Vector3d(0,0,0), Vector3d(0,0,0)};

        bool first = true;
        Vector3d min, max;
        for (auto shape : shapes) {
            AABB b = shape->getBoundingBox();
            if (first) { min = b.min; max = b.max; first = false; }
            else {
                min = (min < b.min).combine(min, b.min);
                max = (max > b.max).combine(max, b.max);
            }
        }
        return {min, max};
    }

protected:
    std::vector<const IShape*> shapes;

private:
    std::unique_ptr<BVHNode> root;
    bool bvhBuilt = false;

    // Метод обхода дерева
    bool traverse(const BVHNode* node, const Ray& ray, float t_min, float t_max, HitRecord& hit) const noexcept;
};

#endif
