//
// Created by iliya on 4/20/26.
//

#include <cmath>
#include <algorithm>
#include "orientedbox.h"

OrientedBox::OrientedBox(const Vector3d& c, const Vector3d& size, const Vector3d& rot, std::shared_ptr<IMaterial> m)
        : center(c), half_size(size * 0.5f), rotation(rot), mat(m) {}

bool OrientedBox::intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const {
    Vector3d local_o = eulerRotateInverse(ray.origin - center, rotation.getX(), rotation.getY(), rotation.getZ());
    Vector3d local_d = eulerRotateInverse(ray.direction, rotation.getX(), rotation.getY(), rotation.getZ());

    float tmin = t_min, tmax = t_max;
    Vector3d normal(0,0,0);

    for (int i = 0; i < 3; ++i) {
        float inv_d = 1.0f / (i==0 ? local_d.getX() : i==1 ? local_d.getY() : local_d.getZ());
        float t0 = ((i==0 ? -half_size.getX() : i==1 ? -half_size.getY() : -half_size.getZ()) - (i==0 ? local_o.getX() : i==1 ? local_o.getY() : local_o.getZ())) * inv_d;
        float t1 = ((i==0 ? half_size.getX() : i==1 ? half_size.getY() : half_size.getZ()) - (i==0 ? local_o.getX() : i==1 ? local_o.getY() : local_o.getZ())) * inv_d;

        if (inv_d < 0) std::swap(t0, t1);

        tmin = std::max(tmin, std::min(t0, t1));
        tmax = std::min(tmax, std::max(t0, t1));

        if (tmin > tmax) return false;
    }

    if (tmin > t_max || tmax < t_min) return false;

    float t = (tmin > t_min) ? tmin : tmax;

    Vector3d local_p = local_o + t * local_d;
    const float eps = 1e-5f;
    Vector3d local_n(0,0,0);
    for (int i = 0; i < 3; ++i) {
        float p_i = (i==0) ? local_p.getX() : (i==1) ? local_p.getY() : local_p.getZ();
        float half_i = (i==0) ? half_size.getX() : (i==1) ? half_size.getY() : half_size.getZ();
        if (std::abs(std::abs(p_i) - half_i) < eps) {
            if (i == 0) local_n = Vector3d(std::copysign(1.0f, p_i), 0, 0);
            else if (i == 1) local_n = Vector3d(0, std::copysign(1.0f, p_i), 0);
            else local_n = Vector3d(0, 0, std::copysign(1.0f, p_i));
            break;
        }
    }

    hit.t = t;
    hit.point = center + eulerRotate(local_p, rotation.getX(), rotation.getY(), rotation.getZ());
    hit.normal = eulerRotate(local_n, rotation.getX(), rotation.getY(), rotation.getZ());
    hit.material = mat.get();
    hit.frontFace = (ray.direction * hit.normal < 0.0f);
    return true;
}

AABB OrientedBox::getBoundingBox() const {
    Vector3d corners[8] = {
            {-half_size.getX(), -half_size.getY(), -half_size.getZ()},
            { half_size.getX(), -half_size.getY(), -half_size.getZ()},
            {-half_size.getX(),  half_size.getY(), -half_size.getZ()},
            { half_size.getX(),  half_size.getY(), -half_size.getZ()},
            {-half_size.getX(), -half_size.getY(),  half_size.getZ()},
            { half_size.getX(), -half_size.getY(),  half_size.getZ()},
            {-half_size.getX(),  half_size.getY(),  half_size.getZ()},
            { half_size.getX(),  half_size.getY(),  half_size.getZ()}
    };

    Vector3d min(1e9f, 1e9f, 1e9f);
    Vector3d max(-1e9f, -1e9f, -1e9f);

    for (auto& c : corners) {
        Vector3d world_c = center + eulerRotate(c, rotation.getX(), rotation.getY(), rotation.getZ());
        min = Vector3d(std::min(min.getX(), world_c.getX()), std::min(min.getY(), world_c.getY()), std::min(min.getZ(), world_c.getZ()));
        max = Vector3d(std::max(max.getX(), world_c.getX()), std::max(max.getY(), world_c.getY()), std::max(max.getZ(), world_c.getZ()));
    }
    return {min, max};
}
