//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/core.h"
#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_GEOMETRY_HIT_RECORD_H
#define CAPI_TRACER_GEOMETRY_HIT_RECORD_H
EXTERN_PREFIX

make_capi(HitRecord);
make_capi(IMaterial);

ccls(HitRecord) HitRecord_empty();
ccls(HitRecord) HitRecord_copy(const ccls(HitRecord) other);
void HitRecord_destroy(ccls(HitRecord) self);

const float HitRecord_get_t(const ccls(HitRecord) self);
void HitRecord_set_t(ccls(HitRecord) self, float t);

const ccls(Vector3d) HitRecord_get_point(const ccls(HitRecord) self);
void HitRecord_set_point(ccls(HitRecord) self, const ccls(Vector3d) point);

const ccls(Vector3d) HitRecord_get_normal(const ccls(HitRecord) self);
void HitRecord_set_normal(ccls(HitRecord) self, const ccls(Vector3d) normal);

const ccls(IMaterial) HitRecord_get_material(const ccls(HitRecord) self);
void HitRecord_set_material(ccls(HitRecord) self, const ccls(IMaterial) material);

const bool HitRecord_get_frontFace(const ccls(HitRecord) self);
void HitRecord_set_frontFace(ccls(HitRecord) self, bool frontFace);

EXTERN_POSTFIX
#endif // CAPI_TRACER_GEOMETRY_HIT_RECORD_H
