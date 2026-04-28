//
// Created by iliya on 4/19/26.
//

#include <cmath>
#include "sphere.h"
#include "tracer/geometry.h"

Sphere::Sphere(const Vector3d &center, float radius, const IMaterial* mat): center(center), radius(radius), mat(mat) {}

bool Sphere::intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const {
    // Базовое пересечение луча со сферой
    Vector3d oc = ray.origin - center;

    float a = ray.direction ^ ray.direction;
    float b = 2.0f * (oc ^ ray.direction);
    float c = (oc ^ oc) - radius*radius;

    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) return false;
    float sqrt_d = sqrt(discriminant);
    float t = (-b - sqrt_d) / (2*a);

    if (t < t_min || t > t_max) {
        t = (-b + sqrt_d) / (2*a);
        if (t < t_min || t > t_max) return false;
    }

    hit.t = t;
    hit.point = ray.at(t);
    hit.normal = (hit.point - center) / radius;
    hit.material = mat;
    hit.frontFace = (ray.direction ^ hit.normal) < 0.0f;
    return true;
}

AABB Sphere::getBoundingBox() const {
    Vector3d r(radius, radius, radius);
    return {center - r, center + r};
}
