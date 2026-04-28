//
// Created by iliya on 4/20/26.
//

#include <cmath>
#include <algorithm>
#include "orientedbox.h"
#include "tracer/geometry.h"

OrientedBox::OrientedBox(const Vector3d& c, const Vector3d& size, const Float3& rot, const IMaterial* m)
        : center(c), half_size(size / 2.f),
              rotation(eulerRotate       (rot.x, rot.y, rot.z)),
          inv_rotation(eulerRotateInverse(rot.x, rot.y, rot.z)),
          mat(m) {}

bool OrientedBox::intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const {
    Vector3d local_o = inv_rotation^(ray.origin - center);
    Vector3d local_d = (inv_rotation^ray.direction).normalize();

    Vector3d inv_d = Vector3d(1.0f) / local_d;
    Vector3d t0 = (-half_size - local_o) * inv_d;
    Vector3d t1 = ( half_size - local_o) * inv_d;

    // Упорядочивание интервалов
    LogicalMask3d inv_neg = (inv_d < 0.0f);
    Vector3d new_t0 = inv_neg.combine(t1, t0);
    Vector3d new_t1 = inv_neg.combine(t0, t1);
    t0 = new_t0;
    t1 = new_t1;

    float t_enter = t0.max();
    float t_exit  = t1.min();

    // Проверка на промах
    if (t_enter > t_exit) return false;
    if (t_exit < t_min || t_enter > t_max) return false;

    // Определение реальной точки пересечения
    float t = (t_enter > t_min) ? t_enter : t_exit;

    // Вычисление локальной точки и нормали
    Vector3d local_p = local_o + t * local_d;
    const float eps = 1e-5f;

    // Поиск нормали через маску
    LogicalMask3d ln_mask = ((local_p.abs() - half_size).abs() < eps);
    Vector3d local_n = ln_mask.combine(local_p.sign(), Vector3d(0.0f));

    hit.t = t;
    hit.point = center + (rotation ^ local_p);
    hit.normal = (rotation ^ local_n).normalize();
    hit.material = mat;
    hit.frontFace = (ray.direction ^ hit.normal) < 0.0f;
    return true;
}

// TODO - переделать на актуальные методы
AABB OrientedBox::getBoundingBox() const {
//    Vector3d corners[8] = {
//            {-half_size.getX(), -half_size.getY(), -half_size.getZ()},
//            { half_size.getX(), -half_size.getY(), -half_size.getZ()},
//            {-half_size.getX(),  half_size.getY(), -half_size.getZ()},
//            { half_size.getX(),  half_size.getY(), -half_size.getZ()},
//            {-half_size.getX(), -half_size.getY(),  half_size.getZ()},
//            { half_size.getX(), -half_size.getY(),  half_size.getZ()},
//            {-half_size.getX(),  half_size.getY(),  half_size.getZ()},
//            { half_size.getX(),  half_size.getY(),  half_size.getZ()}
//    };
//
//    Vector3d min(1e9f, 1e9f, 1e9f);
//    Vector3d max(-1e9f, -1e9f, -1e9f);
//
//    for (auto& c : corners) {
//        Vector3d world_c = center + eulerRotate(c, rotation.x, rotation.y, rotation.z);
//        min = Vector3d(std::min(min.getX(), world_c.getX()), std::min(min.getY(), world_c.getY()), std::min(min.getZ(), world_c.getZ()));
//        max = Vector3d(std::max(max.getX(), world_c.getX()), std::max(max.getY(), world_c.getY()), std::max(max.getZ(), world_c.getZ()));
//    }
    return {{0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}};
}
