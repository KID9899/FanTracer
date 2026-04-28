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
    Vector3d center;
    // Радиус основания
    float radius;
    // Высота
    float height;
    // Матрицы поворота
    Matrix3d rotation;
    Matrix3d inv_rotation;
    // Материал цилиндра
    const IMaterial* mat;
public:
    Cylinder(const Vector3d& c, float r, float h, const Float3& rot, const IMaterial* m);

    bool intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const override;
    AABB getBoundingBox() const override;
};

#endif // TRACER_SHAPES_CYLINDER_H
