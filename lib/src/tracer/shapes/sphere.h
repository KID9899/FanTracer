//
// Created by iliya on 4/19/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_SHAPES_SPHERE_H
#define TRACER_SHAPES_SPHERE_H

// Простая сфера
class Sphere : public IShape {
private:
    // Центр сферы
    const Vector3d center;
    // Радиус сферы
    const float radius;
    // Материал
    const IMaterial *const mat;
public:
    Sphere(const Vector3d &center, float radius, const IMaterial *mat) noexcept;

    bool intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const noexcept override;
    virtual AABB getBoundingBox() const noexcept override;
};

#endif // TRACER_SHAPES_SPHERE_H
