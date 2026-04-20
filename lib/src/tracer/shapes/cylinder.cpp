//
// Created by iliya on 4/20/26.
//

#include <cmath>
#include "cylinder.h"

Cylinder::Cylinder(const Vector3d& c, float r, float h, const Vector3d& rot,
                   std::shared_ptr<IMaterial> m)
        : center(c), radius(r), height(h), rotation(rot), mat(m) {}

bool Cylinder::intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const {
    Vector3d local_o = eulerRotateInverse(ray.origin - center, rotation.getX(), rotation.getY(), rotation.getZ());
    Vector3d local_d = eulerRotateInverse(ray.direction, rotation.getX(), rotation.getY(), rotation.getZ()).normalize();

    float a = local_d.getX()*local_d.getX() + local_d.getY()*local_d.getY();
    float b = 2.0f * (local_o.getX()*local_d.getX() + local_o.getY()*local_d.getY());
    float c = local_o.getX()*local_o.getX() + local_o.getY()*local_o.getY() - radius*radius;

    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) return false;

    float sqrt_d = std::sqrt(discriminant);
    float t1 = (-b - sqrt_d) / (2*a);
    float t2 = (-b + sqrt_d) / (2*a);

    float t = -1.0f;
    Vector3d local_p, local_n;

    auto check_wall = [&](float tt) {
        if (tt < t_min || tt > t_max) return false;
        Vector3d p = local_o + tt * local_d;
        if (p.getZ() < 0 || p.getZ() > height) return false;
        t = tt;
        local_p = p;
        local_n = Vector3d(p.getX(), p.getY(), 0).normalize();
        return true;
    };

    if (!check_wall(t1)) check_wall(t2);

    auto check_cap = [&](float z_cap, const Vector3d& n_cap) {
        if (std::abs(local_d.getZ()) < 1e-8f) return false;
        float t_cap = (z_cap - local_o.getZ()) / local_d.getZ();
        if (t_cap < t_min || t_cap > t_max) return false;
        Vector3d p = local_o + t_cap * local_d;
        if (p.getX()*p.getX() + p.getY()*p.getY() > radius*radius) return false;
        if (t < 0 || t_cap < t) {
            t = t_cap;
            local_p = p;
            local_n = n_cap;
        }
        return true;
    };

    check_cap(0.0f, Vector3d(0,0,-1));
    check_cap(height, Vector3d(0,0,1));

    if (t < 0) return false;

    hit.t = t;
    hit.point = center + eulerRotate(local_p, rotation.getX(), rotation.getY(), rotation.getZ());
    hit.normal = eulerRotate(local_n, rotation.getX(), rotation.getY(), rotation.getZ()).normalize();
    hit.material = mat.get();
    hit.frontFace = (ray.direction * hit.normal < 0.0f);
    return true;
}

AABB Cylinder::getBoundingBox() const {
    const float r = radius;
    const float h = height;
    Vector3d half(Vector3d(r, r, h/2.0f));
    Vector3d c_local(0, 0, h/2.0f);
    return {center - half, center + half};
}
