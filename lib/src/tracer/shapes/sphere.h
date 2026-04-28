//
// Created by iliya on 4/19/26.
//

#include <memory>
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
    float radius;
    // Материал
    const IMaterial* mat;
public:
    Sphere(const Vector3d &center, float radius, const IMaterial* mat);

    bool intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const override;
    virtual AABB getBoundingBox() const override;
};

#endif // TRACER_SHAPES_SPHERE_H
