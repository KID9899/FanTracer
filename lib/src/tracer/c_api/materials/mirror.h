//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"

#ifndef CAPI_TRACER_MATERIALS_MIRROR_H
#define CAPI_TRACER_MATERIALS_MIRROR_H
EXTERN_PREFIX

make_capi(Mirror);

ccls(IMaterial) Mirror2IMaterial(ccls(Mirror) obj);
ccls(Mirror) IMaterial2Mirror(ccls(IMaterial) obj);
const ccls(IMaterial) const_Mirror2IMaterial(const ccls(Mirror) obj);
const ccls(Mirror) const_IMaterial2Mirror(const ccls(IMaterial) obj);

ccls(Mirror) Mirror_make(const ccls(Vector3d) albedo, float fuzz);
void Mirror_destroy(ccls(Mirror) self);
bool Mirror_scatter(const ccls(Mirror) self, const ccls(Ray) in, const ccls(HitRecord) hit, ccls(Vector3d)* absorption_attenuation, ccls(Vector3d)* distortion_attenuation, ccls(Ray)* scattered);
ccls(Vector3d) Mirror_emitted(const ccls(Mirror) self, const ccls(HitRecord) hit);

EXTERN_POSTFIX
#endif // CAPI_TRACER_MATERIALS_MIRROR_H