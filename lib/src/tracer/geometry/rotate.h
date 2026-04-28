//
// Created by iliya on 4/20/26.
//

#include "tracer/core.h"

#ifndef TRACER_GEOMETRY_ROTATION_H
#define TRACER_GEOMETRY_ROTATION_H

// Простое вращение относительно осей
Matrix3d rotateAroundX(float angle);
Matrix3d rotateAroundY(float angle);
Matrix3d rotateAroundZ(float angle);

// Вращение по нескольким углам и обратное вращение
Matrix3d eulerRotate(float rx, float ry, float rz);
Matrix3d eulerRotateInverse(float rx, float ry, float rz);

// Отражение относительно заданной оси
Vector3d reflect(const Vector3d &vec, const Vector3d &axis);

#endif // TRACER_GEOMETRY_ROTATION_H

