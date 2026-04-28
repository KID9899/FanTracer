//
// Created by iliya on 4/19/26.
//

#include "scene.h"

const std::vector<const IShape*> &Scene::getShapes() const { return shapes; }
const std::vector<const ILight*> &Scene::getLights() const { return lights; }

void Scene::add(const IShape* shape) {
    shapes.push_back(shape);
}

void Scene::add(const ILight* light) {
    lights.push_back(light);
}

bool Scene::intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const {
    HitRecord temp;
    bool hit_anything = false;
    float closest_so_far = t_max;

    for (const auto& shape : shapes) {
        if (shape->intersect(ray, t_min, closest_so_far, temp)) {
            hit_anything = true;
            closest_so_far = temp.t;
            hit = temp;
        }
    }
    return hit_anything;
}
