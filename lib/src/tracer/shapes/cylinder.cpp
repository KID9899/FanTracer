//
// Created by iliya on 4/20/26.
//

#include <cmath>
#include "cylinder.h"
#include "tracer/geometry.h"

Cylinder::Cylinder(const Vector3d& c, float r, float h, const Float3& rot, const IMaterial* m)
        : center(c), radius(r), height(h),
              rotation(eulerRotate       (rot.x, rot.y, rot.z)),
          inv_rotation(eulerRotateInverse(rot.x, rot.y, rot.z)),
          mat(m) {}

bool Cylinder::intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const {
    // Переводим луч в относительный координаты (центр цилиндра в начале координат, цидиндр строго вертикально)
    Vector3d local_o = inv_rotation^(ray.origin - center);
    Vector3d local_d = (inv_rotation^ray.direction).normalize();

    // Проверяем, есть ли пересечения с бесконечным цилиндром нашего радиуса
    float a = local_d.dotXY(local_d);
    float b = 2.0f * local_o.dotXY(local_d);
    float c = local_o.dotXY(local_o) - radius*radius;

    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) return false;

    // Если есть, то где
    float sqrt_d = std::sqrt(discriminant);
    float t1 = (-b - sqrt_d) / (2*a);
    float t2 = (-b + sqrt_d) / (2*a);

    // Тут будут итоговые t, pos и normal
    float t = -1.0f;
    Vector3d local_p, local_n;

    // Функция для проверки, есть ли пересечение с основанием
    auto check_wall = [&](float tt) {
        if (tt < t_min || tt > t_max) return false;
        Vector3d p = local_o + tt * local_d;
        if ((p < 0 || p > height).z()) return false;
        t = tt;
        local_p = p;
        local_n = p.replaceZ(0.f).normalize();
        return true;
    };

    // Проверяем точки потенциального пересечения
    if (!check_wall(t1)) check_wall(t2);

    // Функция для проверки пересечения с стенкой
    auto check_cap = [&](float z_cap, const Vector3d& n_cap) {
        float z = local_d.getZ();
        if (std::abs(z) < 1e-8f) return false;
        float t_cap = (z_cap - z) / z;
        if (t_cap < t_min || t_cap > t_max) return false;
        Vector3d p = local_o + t_cap * local_d;
        if (p.dotXY(p) > radius*radius) return false;
        if (t < 0 || t_cap < t) {
            t = t_cap;
            local_p = p;
            local_n = n_cap;
        }
        return true;
    };

    // Проверяем есть ли пересечения с основаниями
    check_cap(0.0f, Vector3d(0.f,0.f,-1.f));
    check_cap(height, Vector3d(0.f,0.f,1.f));

    // Если так ничего и не нашли
    if (t < 0) return false;

    // Записываем результат
    hit.t = t;
    hit.point = center + (rotation ^ local_p);
    hit.normal = (rotation ^ local_n).normalize();
    hit.material = mat;
    hit.frontFace = (ray.direction ^ hit.normal) < 0.0f;
    return true;
}

AABB Cylinder::getBoundingBox() const {
    const float r = radius;
    const float h = height;
    Vector3d half(Vector3d(r, r, h/2.0f));
    Vector3d c_local(0, 0, h/2.0f);
    return {center - half, center + half};
}
