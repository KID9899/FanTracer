//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/core.h"
#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_GEOMETRY_AABB_H
#define CAPI_TRACER_GEOMETRY_AABB_H
EXTERN_PREFIX

make_capi(AABB);

ccls(AABB) AABB_empty();
ccls(AABB) AABB_make(const ccls(Vector3d) min, const ccls(Vector3d) max);
ccls(AABB) AABB_copy(const ccls(AABB) other);
void AABB_destroy(ccls(AABB) self);

ccls(Vector3d) AABB_min(const ccls(AABB) self);
void AABB_set_min(ccls(AABB) self, const ccls(Vector3d) min);
ccls(Vector3d) AABB_max(const ccls(AABB) self);
void AABB_set_max(ccls(AABB) self, const ccls(Vector3d) max);

EXTERN_POSTFIX
#endif // CAPI_TRACER_GEOMETRY_AABB_H
