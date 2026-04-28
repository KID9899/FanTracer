//
// Created by iliya on 4/20/26.
//

#include <xmmintrin.h>
#include <cmath>
#include "rotate.h"

Matrix3d rotateAroundX(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix3d::concatCols(
        {1.f, 0.f, 0.f},
        {0.f,   c,   s},
        {0.f,  -s,   c}
    );
}
Matrix3d rotateAroundY(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix3d::concatCols(
        {  c, 0.f,  -s},
        {0.f, 1.f, 0.f},
        {  s, 0.f,   c}
    );
}
Matrix3d rotateAroundZ(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix3d::concatCols(
        {  c,   s, 0.f},
        { -s,   c, 0.f},
        {0.f, 0.f, 1.f}
    );
}

Matrix3d eulerRotate(float rx, float ry, float rz) {
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
Matrix3d eulerRotateInverse(float rx, float ry, float rz) {
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

Vector3d reflect(const Vector3d &vec, const Vector3d &axis) {
    return vec - 2 * ((vec ^ axis) / (axis ^ axis)) * axis;
}
