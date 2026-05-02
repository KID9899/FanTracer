//
// Created by iliya on 4/20/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_SHAPES_ORIENTEDBOX_H
#define TRACER_SHAPES_ORIENTEDBOX_H

// Простой кубик
class OrientedBox : public IShape {
    // Центр
    const Vector3d center;
    // Вектор половин длинн рёбер
    const Vector3d half_size;
    // Матрицы поворота
    const Matrix3d rotation;
    const Matrix3d inv_rotation;
    // Материал
    const IMaterial *const mat;
public:
    OrientedBox(const Vector3d &c, const Vector3d &size, const Float3 &rot, const IMaterial *m) noexcept;

    bool intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const noexcept override;
    AABB getBoundingBox() const noexcept override;
};

#endif // TRACER_SHAPES_ORIENTEDBOX_H
