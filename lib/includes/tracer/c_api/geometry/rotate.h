//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/core.h"
#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_GEOMETRY_ROTATE_H
#define CAPI_TRACER_GEOMETRY_ROTATE_H
EXTERN_PREFIX

ccls(Matrix3d) geometry_rotateAroundX(float angle);
ccls(Matrix3d) geometry_rotateAroundY(float angle);
ccls(Matrix3d) geometry_rotateAroundZ(float angle);
ccls(Matrix3d) geometry_eulerRotate(float rx, float ry, float rz);
ccls(Matrix3d) geometry_eulerRotateInverse(float rx, float ry, float rz);
ccls(Vector3d) geometry_reflect(const ccls(Vector3d) vec, const ccls(Vector3d) axis);

EXTERN_POSTFIX
#endif // CAPI_TRACER_GEOMETRY_ROTATE_H
