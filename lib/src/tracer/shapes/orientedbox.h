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
    Vector3d center;
    // Вектор половин длинн рёбер
    Vector3d half_size;
    // Матрицы поворота
    Matrix3d rotation;
    Matrix3d inv_rotation;
    // Материал
    const IMaterial* mat;
public:
    OrientedBox(const Vector3d& c, const Vector3d& size, const Float3& rot, const IMaterial* m);

    bool intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const override;
    AABB getBoundingBox() const override;
};

#endif // TRACER_SHAPES_ORIENTEDBOX_H
