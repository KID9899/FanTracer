//
// Created by iliya on 4/20/26.
//

#include <cmath>
#include "plane.h"

Plane::Plane(const Vector3d& p, const Vector3d& n, std::shared_ptr<IMaterial> m)
        : point(p), normal(n.normalize()), mat(m) {}

bool Plane::intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const {
    float denom = ray.direction * normal;
    if (std::abs(denom) < 1e-8f) return false;

    float t = ((point - ray.origin) * normal) / denom;
    if (t < t_min || t > t_max) return false;

    hit.t = t;
    hit.point = ray.at(t);
    hit.normal = (denom < 0.0f) ? normal : -normal;
    hit.material = mat.get();
    hit.frontFace = (denom < 0.0f);
    return true;
}

AABB Plane::getBoundingBox() const {
    const float INF = 1e6f;
    return {Vector3d(-INF, -INF, -INF), Vector3d(INF, INF, INF)};
}
