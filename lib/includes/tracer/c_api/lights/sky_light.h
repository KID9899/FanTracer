//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"

#ifndef CAPI_TRACER_LIGHTS_SKY_LIGHT_H
#define CAPI_TRACER_LIGHTS_SKY_LIGHT_H
EXTERN_PREFIX

make_capi(SkyLight);

ccls(ILight) SkyLight2ILight(ccls(SkyLight) obj);
ccls(SkyLight) ILight2SkyLight(ccls(ILight) obj);
const ccls(ILight) const_SkyLight2ILight(const ccls(SkyLight) obj);
const ccls(SkyLight) const_ILight2SkyLight(const ccls(ILight) obj);

ccls(SkyLight) SkyLight_make(const ccls(Vector3d) intensity);
void SkyLight_destroy(ccls(SkyLight) self);
ccls(Vector3d) SkyLight_illuminate(const ccls(SkyLight) self, const ccls(HitRecord) hit, ccls(Vector3d)* light_dir, float* distance);
ccls(Vector3d) SkyLight_samplePoint(const ccls(SkyLight) self);

EXTERN_POSTFIX
#endif // CAPI_TRACER_LIGHTS_SKY_LIGHT_H
