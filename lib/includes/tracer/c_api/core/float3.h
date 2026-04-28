//
// Created by iliya on 4/26/26.
//

#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_GEOMETRY_FLOAT3_H
#define CAPI_TRACER_GEOMETRY_FLOAT3_H
EXTERN_PREFIX

make_capi(Float3);

ccls(Float3) Float3_make(float x, float y, float z);
ccls(Float3) Float3_empty();
void Float3_destroy(ccls(Float3) self);

float Float3_x(const ccls(Float3) self);
float Float3_y(const ccls(Float3) self);
float Float3_z(const ccls(Float3) self);

void Float3_set_x(ccls(Float3) self, float x);
void Float3_set_y(ccls(Float3) self, float y);
void Float3_set_z(ccls(Float3) self, float z);

EXTERN_POSTFIX
#endif // CAPI_TRACER_GEOMETRY_FLOAT3_H
