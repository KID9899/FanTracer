//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"

#ifndef CAPI_TRACER_MATERIALS_LAMBERTIAN_H
#define CAPI_TRACER_MATERIALS_LAMBERTIAN_H
EXTERN_PREFIX

make_capi(Lambertian);

ccls(IMaterial) Lambertian2IMaterial(ccls(Lambertian) obj);
ccls(Lambertian) IMaterial2Lambertian(ccls(IMaterial) obj);
const ccls(IMaterial) const_Lambertian2IMaterial(const ccls(Lambertian) obj);
const ccls(Lambertian) const_IMaterial2Lambertian(const ccls(IMaterial) obj);

ccls(Lambertian) Lambertian_make(const ccls(Vector3d) color);
void Lambertian_destroy(ccls(Lambertian) self);
bool Lambertian_scatter(const ccls(Lambertian) self, const ccls(Ray) in, const ccls(HitRecord) hit, ccls(Vector3d)* absorption_attenuation, ccls(Vector3d)* distortion_attenuation, ccls(Ray)* scattered);
ccls(Vector3d) Lambertian_emitted(const ccls(Lambertian) self, const ccls(HitRecord) hit);

EXTERN_POSTFIX
#endif // CAPI_TRACER_MATERIALS_LAMBERTIAN_H