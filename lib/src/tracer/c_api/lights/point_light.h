//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"

#ifndef CAPI_TRACER_LIGHTS_POINT_LIGHT_H
#define CAPI_TRACER_LIGHTS_POINT_LIGHT_H
EXTERN_PREFIX

make_capi(PointLight);

ccls(ILight) PointLight2ILight(ccls(PointLight) obj);
ccls(PointLight) ILight2PointLight(ccls(ILight) obj);
const ccls(ILight) const_PointLight2ILight(const ccls(PointLight) obj);
const ccls(PointLight) const_ILight2PointLight(const ccls(ILight) obj);

ccls(PointLight) PointLight_make(const ccls(Vector3d) position, const ccls(Vector3d) intensity);
void PointLight_destroy(ccls(PointLight) self);
ccls(Vector3d) PointLight_illuminate(const ccls(PointLight) self, const ccls(HitRecord) hit, ccls(Vector3d) *light_dir, float *distance);
ccls(Vector3d) PointLight_samplePoint(const ccls(PointLight) self);

EXTERN_POSTFIX
#endif // CAPI_TRACER_LIGHTS_POINT_LIGHT_H
