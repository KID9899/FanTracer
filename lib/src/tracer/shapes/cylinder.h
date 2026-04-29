//
// Created by iliya on 4/20/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_SHAPES_CYLINDER_H
#define TRACER_SHAPES_CYLINDER_H

// Простой цилиндр
class Cylinder : public IShape {
    // Центр цилиндра
    const Vector3d center;
    // Радиус основания
    const float radius;
    // Высота
    const float height;
    // Матрицы поворота
    const Matrix3d rotation;
    const Matrix3d inv_rotation;
    // Материал цилиндра
    const IMaterial *const mat;
public:
    Cylinder(const Vector3d &c, float r, float h, const Float3 &rot, const IMaterial *m) noexcept;

    bool intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const noexcept override;
    AABB getBoundingBox() const noexcept override;
};

#endif // TRACER_SHAPES_CYLINDER_H
