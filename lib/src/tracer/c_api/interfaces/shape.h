//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"
#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_INTERFACES_SHAPE_H
#define CAPI_TRACER_INTERFACES_SHAPE_H
EXTERN_PREFIX

make_capi(IShape);

void IShape_destroy(ccls(IShape) self);
bool IShape_intersect(const ccls(IShape) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord) *hit);
ccls(AABB) IShape_getBoundingBox(const ccls(IShape) self);

EXTERN_POSTFIX
#endif // CAPI_TRACER_INTERFACES_SHAPE_H
