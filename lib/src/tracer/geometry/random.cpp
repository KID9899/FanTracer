//
// Created by iliya on 4/19/26.
//

#include <random>
#include <cmath>
#include "random.h"

const Vector3d randomInUnitSphere() {
    static std::mt19937 gen(std::random_device{}());
    static std::normal_distribution<float> dist(0.0, 1.0);

    float x = dist(gen);
    float y = dist(gen);
    float z = dist(gen);

    float length = std::sqrt(x*x + y*y + z*z);

    if (length == 0) return Vector3d(1, 0, 0);

    return Vector3d(x / length, y / length, z / length);
}
