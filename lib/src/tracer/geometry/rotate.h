//
// Created by iliya on 4/20/26.
//

#include "vector3d.h"

#ifndef TRACER_GEOMETRY_ROTATION_H
#define TRACER_GEOMETRY_ROTATION_H

// Простое вращение относительно осей
Vector3d rotateAroundX(const Vector3d& v, float angle);
Vector3d rotateAroundY(const Vector3d& v, float angle);
Vector3d rotateAroundZ(const Vector3d& v, float angle);

// Вращение по нескольким углам и обратное вращение
Vector3d eulerRotate(const Vector3d& v, float rx, float ry, float rz);
Vector3d eulerRotateInverse(const Vector3d& v, float rx, float ry, float rz);

#endif // TRACER_GEOMETRY_ROTATION_H

