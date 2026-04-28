//
// Created by iliya on 4/26/26.
//

#include <xmmintrin.h>
#include "vector3d.h"
#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_GEOMETRY_LOGICALMASK3D_H
#define CAPI_TRACER_GEOMETRY_LOGICALMASK3D_H
EXTERN_PREFIX

make_capi(LogicalMask3d);

ccls(LogicalMask3d) LogicalMask3d_empty();
ccls(LogicalMask3d) LogicalMask3d_copy(const ccls(LogicalMask3d) copy);
void LogicalMask3d_destroy(ccls(LogicalMask3d) self);

bool LogicalMask3d_x(const ccls(LogicalMask3d) self);
bool LogicalMask3d_y(const ccls(LogicalMask3d) self);
bool LogicalMask3d_z(const ccls(LogicalMask3d) self);

bool LogicalMask3d_any(const ccls(LogicalMask3d) self);
bool LogicalMask3d_all(const ccls(LogicalMask3d) self);

ccls(LogicalMask3d) LogicalMask3d_and(const ccls(LogicalMask3d) self, const ccls(LogicalMask3d) other);
ccls(LogicalMask3d) LogicalMask3d_or(const ccls(LogicalMask3d) self, const ccls(LogicalMask3d) other);
ccls(LogicalMask3d) LogicalMask3d_xor(const ccls(LogicalMask3d) self, const ccls(LogicalMask3d) other);
ccls(LogicalMask3d) LogicalMask3d_not(const ccls(LogicalMask3d) self);

ccls(Vector3d) LogicalMask3d_assign(const ccls(LogicalMask3d) self, const ccls(Vector3d) other);
ccls(Vector3d) LogicalMask3d_combine(const ccls(LogicalMask3d) self, const ccls(Vector3d) true_v, const ccls(Vector3d) false_v);

char LogicalMask3d_toChar(const ccls(LogicalMask3d) self);
ccls(Vector3d) LogicalMask3d_toVector(const ccls(LogicalMask3d) self);

EXTERN_POSTFIX
#endif // CAPI_TRACER_GEOMETRY_LOGICALMASK3D_H
