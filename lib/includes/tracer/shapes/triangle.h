//
// Created by iliya on 5/2/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_SHAPES_TRIANGLE_H
#define TRACER_SHAPES_TRIANGLE_H

// TODO - добавить c_api
class Triangle : public IShape {
    const Vector3d v0, v1, v2;
    const Vector3d normal;
    const IMaterial* const mat;

    // UV
    const Float2 uv0, uv1, uv2;
    const bool hasUV;

public:
    // Без UV
    Triangle(const Vector3d &a, const Vector3d &b, const Vector3d &c, const IMaterial *m) noexcept;
    // С UV
    Triangle(const Vector3d &a, const Vector3d &b, const Vector3d &c,
             const Float2 &uva, const Float2 &uvb, const Float2 &uvc,
             const IMaterial *m) noexcept;

    bool intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const noexcept override;
    AABB getBoundingBox() const noexcept override;
};

#endif // TRACER_SHAPES_TRIANGLE_H
