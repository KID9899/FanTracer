//
// Created by iliya on 4/20/26.
//

#include "tracer/core.h"

#ifndef TRACER_GEOMETRY_ROTATION_H
#define TRACER_GEOMETRY_ROTATION_H

// Простое вращение относительно осей
inline Matrix3d rotateAroundX(float angle) noexcept {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix3d::concatCols(
        {1.f, 0.f, 0.f},
        {0.f,   c,   s},
        {0.f,  -s,   c}
    );
}
inline Matrix3d rotateAroundY(float angle) noexcept {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix3d::concatCols(
        {  c, 0.f,  -s},
        {0.f, 1.f, 0.f},
        {  s, 0.f,   c}
    );
}
inline Matrix3d rotateAroundZ(float angle) noexcept {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix3d::concatCols(
        {  c,   s, 0.f},
        { -s,   c, 0.f},
        {0.f, 0.f, 1.f}
    );
}

// Вращение по нескольким углам и обратное вращение
inline Matrix3d eulerRotate(float rx, float ry, float rz) noexcept {
    float cx = std::cos(rx), sx = std::sin(rx);
    float cy = std::cos(ry), sy = std::sin(ry);
    float cz = std::cos(rz), sz = std::sin(rz);

    float c00 = cy * cz;
    float c10 = cy * sz;
    float c20 = -sy;

    float c01 = cz * sx * sy - cx * sz;
    float c11 = cx * cz + sx * sy * sz;
    float c21 = cy * sx;

    float c02 = cx * cz * sy + sx * sz;
    float c12 = cx * sy * sz - cz * sx;
    float c22 = cx * cy;

    return Matrix3d::concatCols(
        {c00, c10, c20},
        {c01, c11, c21},
        {c02, c12, c22}
    );
}
inline Matrix3d eulerRotateInverse(float rx, float ry, float rz) noexcept {
    float cx = std::cos(rx), sx = std::sin(rx);
    float cy = std::cos(ry), sy = std::sin(ry);
    float cz = std::cos(rz), sz = std::sin(rz);

    float c00 = cy * cz;
    float c10 = cz * sx * sy - cx * sz;
    float c20 = cx * cz * sy + sx * sz;

    float c01 = cy * sz;
    float c11 = cx * cz + sx * sy * sz;
    float c21 = cx * sy * sz - cz * sx;

    float c02 = -sy;
    float c12 = cy * sx;
    float c22 = cx * cy;

    return Matrix3d::concatCols(
        {c00, c10, c20},
        {c01, c11, c21},
        {c02, c12, c22}
    );
}

// Отражение относительно заданной оси
inline Vector3d reflect(const Vector3d &vec, const Vector3d &axis) noexcept {
    return vec - 2 * ((vec ^ axis) / (axis ^ axis)) * axis;
}

#endif // TRACER_GEOMETRY_ROTATION_H

