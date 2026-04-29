//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"

#ifndef CAPI_TRACER_MATERIALS_GLASS_H
#define CAPI_TRACER_MATERIALS_GLASS_H
EXTERN_PREFIX

make_capi(Glass);

ccls(IMaterial) Glass2IMaterial(ccls(Glass) obj);
ccls(Glass) IMaterial2Glass(ccls(IMaterial) obj);
const ccls(IMaterial) const_Glass2IMaterial(const ccls(Glass) obj);
const ccls(Glass) const_IMaterial2Glass(const ccls(IMaterial) obj);

ccls(Glass) Glass_make(const ccls(Vector3d) color, float refraction_index, float reflection_coeff, float tint_coeff);
void Glass_destroy(ccls(Glass) self);
bool Glass_scatter(const ccls(Glass) self, const ccls(Ray) in, const ccls(HitRecord) hit, ccls(Vector3d) *absorption_attenuation, ccls(Vector3d) *distortion_attenuation, ccls(Ray) *scattered);
ccls(Vector3d) Glass_emitted(const ccls(Glass) self, const ccls(HitRecord) hit);

EXTERN_POSTFIX
#endif // CAPI_TRACER_MATERIALS_GLASS_H