//
// Created by iliya on 4/26/26.
//

#include <xmmintrin.h>
#include "vector3d.h"
#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_GEOMETRY_MATRIX3D_H
#define CAPI_TRACER_GEOMETRY_MATRIX3D_H
EXTERN_PREFIX

make_capi(Matrix3d);

ccls(Matrix3d) Matrix3d_empty();
ccls(Matrix3d) Matrix3d_concatCols(ccls(Float3) col0, ccls(Float3) col1, ccls(Float3) col2);
ccls(Matrix3d) Matrix3d_concatRows(ccls(Float3) row0, ccls(Float3) row1, ccls(Float3) row2);
ccls(Matrix3d) Matrix3d_eye();
ccls(Matrix3d) Matrix3d_diag(float x);
ccls(Matrix3d) Matrix3d_fill(float x);
ccls(Matrix3d) Matrix3d_copy(const ccls(Matrix3d) other);
void Matrix3d_destroy(ccls(Matrix3d) self);

ccls(Matrix3d) Matrix3d_add_assign(ccls(Matrix3d) self, const ccls(Matrix3d) other);
ccls(Matrix3d) Matrix3d_sub_assign(ccls(Matrix3d) self, const ccls(Matrix3d) other);
ccls(Matrix3d) Matrix3d_mul_assign(ccls(Matrix3d) self, const ccls(Matrix3d) other);
ccls(Matrix3d) Matrix3d_div_assign(ccls(Matrix3d) self, const ccls(Matrix3d) other);
ccls(Matrix3d) Matrix3d_smul_assign(ccls(Matrix3d) self, float scalar);
ccls(Matrix3d) Matrix3d_sdiv_assign(ccls(Matrix3d) self, float scalar);

ccls(Matrix3d) Matrix3d_add(const ccls(Matrix3d) lhs, const ccls(Matrix3d) rhs);
ccls(Matrix3d) Matrix3d_sub(const ccls(Matrix3d) lhs, const ccls(Matrix3d) rhs);
ccls(Matrix3d) Matrix3d_mul(const ccls(Matrix3d) lhs, const ccls(Matrix3d) rhs);
ccls(Matrix3d) Matrix3d_div(const ccls(Matrix3d) lhs, const ccls(Matrix3d) rhs);
ccls(Matrix3d) Matrix3d_smul(const ccls(Matrix3d) lhs, float scalar);
ccls(Matrix3d) Matrix3d_sdiv(const ccls(Matrix3d) lhs, float scalar);

ccls(Vector3d) Matrix3d_apply(const ccls(Matrix3d) self, const ccls(Vector3d) v);

EXTERN_POSTFIX
#endif // CAPI_TRACER_GEOMETRY_MATRIX3D_H