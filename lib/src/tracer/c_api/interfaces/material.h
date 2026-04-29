//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"
#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_INTERFACES_MATERIAL_H
#define CAPI_TRACER_INTERFACES_MATERIAL_H
EXTERN_PREFIX

make_capi(IMaterial);

void IMaterial_destroy(ccls(IMaterial) self);
bool IMaterial_scatter(const ccls(IMaterial) self, const ccls(Ray) in, const ccls(HitRecord) hit, ccls(Vector3d) *absorption_attenuation, ccls(Vector3d) *distortion_attenuation, ccls(Ray) *scattered);
ccls(Vector3d) IMaterial_emitted(const ccls(IMaterial) self, const ccls(HitRecord) hit);

EXTERN_POSTFIX
#endif // CAPI_TRACER_INTERFACES_MATERIAL_H
