//
// Created by iliya on 4/20/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_SHAPES_PLANE_H
#define TRACER_SHAPES_PLANE_H

// Классическая бесконечная плоскость
class Plane : public IShape {
    // Одна из точек плоскости
    const Vector3d point;
    // Нормаль к этой плоскости
    const Vector3d normal;
    // Материал плоскости
    const IMaterial *const mat;
public:
    Plane(const Vector3d &p, const Vector3d &n, const IMaterial *m) noexcept;

    bool intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const noexcept override;
    AABB getBoundingBox() const noexcept override;
};

#endif // TRACER_SHAPES_PLANE_H
