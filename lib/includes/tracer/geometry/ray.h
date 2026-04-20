//
// Created by iliya on 4/19/26.
//

#include "vector3d.h"
#include "funny_defines/classes.h"

#ifndef TRACER_GEOMETRY_RAY_H
#define TRACER_GEOMETRY_RAY_H

// Простая структура луча
// TODO - Добавить механику пакетов для SIMD
struct Ray {
    // Начало
    Vector3d origin;
    // Направление
    Vector3d direction;

    // Точка на расстоянии t от начала по направлению луча
    const Vector3d at(float t) const;
};

#endif // TRACER_GEOMETRY_RAY_H
