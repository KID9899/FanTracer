//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"

#ifndef CAPI_TRACER_SHAPES_SPHERE_H
#define CAPI_TRACER_SHAPES_SPHERE_H
EXTERN_PREFIX

make_capi(Sphere);

ccls(IShape) Sphere2IShape(ccls(Sphere) obj);
ccls(Sphere) IShape2Sphere(ccls(IShape) obj);
const ccls(IShape) const_Sphere2IShape(const ccls(Sphere) obj);
const ccls(Sphere) const_IShape2Sphere(const ccls(IShape) obj);

ccls(Sphere) Sphere_make(const ccls(Vector3d) center, float radius, const ccls(IMaterial) material);
void Sphere_destroy(ccls(Sphere) self);
bool Sphere_intersect(const ccls(Sphere) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord) *hit);
ccls(AABB) Sphere_getBoundingBox(const ccls(Sphere) self);

EXTERN_POSTFIX
#endif // CAPI_TRACER_SHAPES_SPHERE_H