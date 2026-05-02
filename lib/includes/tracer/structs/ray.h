//
// Created by iliya on 4/19/26.
//

#include "tracer/core.h"

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
    inline const Vector3d at(float t) const noexcept {
        return origin + t * direction;
    }
};

#endif // TRACER_GEOMETRY_RAY_H
