//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/core.h"
#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_GEOMETRY_RAY_H
#define CAPI_TRACER_GEOMETRY_RAY_H
EXTERN_PREFIX

make_capi(Ray);

ccls(Ray) Ray_empty();
ccls(Ray) Ray_make(const ccls(Vector3d) origin, const ccls(Vector3d) direction);
ccls(Ray) Ray_copy(const ccls(Ray) other);
void Ray_destroy(ccls(Ray) self);

ccls(Vector3d) Ray_origin(const ccls(Ray) self);
ccls(Vector3d) Ray_direction(const ccls(Ray) self);
ccls(Vector3d) Ray_at(const ccls(Ray) self, float t);

EXTERN_POSTFIX
#endif // CAPI_TRACER_GEOMETRY_RAY_H
