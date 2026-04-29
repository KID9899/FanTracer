//
// Created by iliya on 4/19/26.
//

#include <random>
#include <cmath>
#include "tracer/core.h"

#ifndef TRACER_GEOMETRY_RANDOM_H
#define TRACER_GEOMETRY_RANDOM_H

// Случайная точка на сфере радиуса 1
inline Vector3d randomInUnitSphere() noexcept {
    static std::mt19937 gen(std::random_device{}());
    static std::normal_distribution<float> dist(0.0, 1.0);

    float x = dist(gen);
    float y = dist(gen);
    float z = dist(gen);

    return Vector3d(x, y, z).normalize();
}

#endif // TRACER_GEOMETRY_RANDOM_H
