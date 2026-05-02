//
// Created by iliya on 5/2/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_SHAPES_TRIANGLE_H
#define TRACER_SHAPES_TRIANGLE_H

class Triangle : public IShape {
    // Координаты углов
    const Vector3d v0, v1, v2;
    // Предпосчитанный вектор нормали
    const Vector3d normal;
    // Собственно, материал
    const IMaterial *const mat;
public:
    Triangle(const Vector3d &a, const Vector3d &b, const Vector3d &c, const IMaterial *m) noexcept;

    bool intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const noexcept override;
    AABB getBoundingBox() const noexcept override;
};

#endif // TRACER_SHAPES_TRIANGLE_H
