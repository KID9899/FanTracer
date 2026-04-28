//
// Created by iliya on 4/26/26.
//

#include <xmmintrin.h>
#include "float3.h"
#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_GEOMETRY_VECTOR3D_H
#define CAPI_TRACER_GEOMETRY_VECTOR3D_H
EXTERN_PREFIX

make_capi(Vector3d);
make_capi(LogicalMask3d);

ccls(Vector3d) Vector3d_copy(const ccls(Vector3d) copy);
ccls(Vector3d) Vector3d_make(float x, float y, float z);
ccls(Vector3d) Vector3d_fill(float fill);
ccls(Vector3d) Vector3d_empty();
ccls(Vector3d) Vector3d_from_f3(const ccls(Float3) f3);
ccls(Vector3d) Vector3d_unsafeCreateFromXMM(__m128 data);

void Vector3d_destroy(ccls(Vector3d) self);

float Vector3d_getX(const ccls(Vector3d) self);
float Vector3d_getY(const ccls(Vector3d) self);
float Vector3d_getZ(const ccls(Vector3d) self);
__m128 Vector3d_getData(const ccls(Vector3d) self);


ccls(Vector3d) Vector3d_replaceX(const ccls(Vector3d) self, float newX);
ccls(Vector3d) Vector3d_replaceY(const ccls(Vector3d) self, float newY);
ccls(Vector3d) Vector3d_replaceZ(const ccls(Vector3d) self, float newZ);


float Vector3d_dot(const ccls(Vector3d) self, const ccls(Vector3d) other);
float Vector3d_dotXY(const ccls(Vector3d) self, const ccls(Vector3d) other);
float Vector3d_dotXZ(const ccls(Vector3d) self, const ccls(Vector3d) other);
float Vector3d_dotYZ(const ccls(Vector3d) self, const ccls(Vector3d) other);


ccls(Vector3d) Vector3d_add_assign(ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(Vector3d) Vector3d_sub_assign(ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(Vector3d) Vector3d_mul_assign(ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(Vector3d) Vector3d_div_assign(ccls(Vector3d) self, const ccls(Vector3d) other);

ccls(Vector3d) Vector3d_smul_assign(ccls(Vector3d) self, float scalar);
ccls(Vector3d) Vector3d_sdiv_assign(ccls(Vector3d) self, float scalar);

ccls(Vector3d) Vector3d_neg(const ccls(Vector3d) self);

ccls(Vector3d) Vector3d_and_assign(ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(Vector3d) Vector3d_or_assign(ccls(Vector3d) self, const ccls(Vector3d) other);


float Vector3d_hypot(const ccls(Vector3d) self);
float Vector3d_length(const ccls(Vector3d) self);


float Vector3d_max(const ccls(Vector3d) self);
float Vector3d_min(const ccls(Vector3d) self);

ccls(Vector3d) Vector3d_abs(const ccls(Vector3d) self);
ccls(Vector3d) Vector3d_sign(const ccls(Vector3d) self);
ccls(Vector3d) Vector3d_normalize(const ccls(Vector3d) self);

ccls(Vector3d) Vector3d_cross(const ccls(Vector3d) self, const ccls(Vector3d) other);

ccls(Vector3d) Vector3d_add(const ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(Vector3d) Vector3d_sub(const ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(Vector3d) Vector3d_mul(const ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(Vector3d) Vector3d_div(const ccls(Vector3d) self, const ccls(Vector3d) other);

ccls(Vector3d) Vector3d_smul(const ccls(Vector3d) self, float scalar);
ccls(Vector3d) Vector3d_sdiv(const ccls(Vector3d) self, float scalar);

ccls(Vector3d) Vector3d_and(const ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(Vector3d) Vector3d_or(const ccls(Vector3d) self, const ccls(Vector3d) other);


ccls(LogicalMask3d) Vector3d_eq(const ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(LogicalMask3d) Vector3d_gt(const ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(LogicalMask3d) Vector3d_lt(const ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(LogicalMask3d) Vector3d_ge(const ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(LogicalMask3d) Vector3d_le(const ccls(Vector3d) self, const ccls(Vector3d) other);
ccls(LogicalMask3d) Vector3d_neq(const ccls(Vector3d) self, const ccls(Vector3d) other);

ccls(LogicalMask3d) Vector3d_seq(const ccls(Vector3d) self, float other);
ccls(LogicalMask3d) Vector3d_sgt(const ccls(Vector3d) self, float other);
ccls(LogicalMask3d) Vector3d_slt(const ccls(Vector3d) self, float other);
ccls(LogicalMask3d) Vector3d_sge(const ccls(Vector3d) self, float other);
ccls(LogicalMask3d) Vector3d_sle(const ccls(Vector3d) self, float other);
ccls(LogicalMask3d) Vector3d_sneq(const ccls(Vector3d) self, float other);

ccls(LogicalMask3d) Vector3d_toMask(const ccls(Vector3d) self);

EXTERN_POSTFIX
#endif // CAPI_TRACER_GEOMETRY_VECTOR3D_H
