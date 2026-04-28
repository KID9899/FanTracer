//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"
#include "funny_defines/c_api.h"

#ifndef CAPI_TRACER_INTERFACES_LIGHT_H
#define CAPI_TRACER_INTERFACES_LIGHT_H
EXTERN_PREFIX

make_capi(ILight);

void ILight_destroy(ccls(ILight) self);
ccls(Vector3d) ILight_illuminate(const ccls(ILight) self, const ccls(HitRecord) hit, ccls(Vector3d)* light_dir, float* distance);
ccls(Vector3d) ILight_samplePoint(const ccls(ILight) self);

EXTERN_POSTFIX
#endif // CAPI_TRACER_INTERFACES_LIGHT_H
