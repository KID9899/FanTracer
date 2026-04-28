//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"

#ifndef CAPI_TRACER_SHAPES_PLANE_H
#define CAPI_TRACER_SHAPES_PLANE_H
EXTERN_PREFIX

make_capi(Plane);

ccls(IShape) Plane2IShape(ccls(Plane) obj);
ccls(Plane) IShape2Plane(ccls(IShape) obj);
const ccls(IShape) const_Plane2IShape(const ccls(Plane) obj);
const ccls(Plane) const_IShape2Plane(const ccls(IShape) obj);

ccls(Plane) Plane_make(const ccls(Vector3d) point, const ccls(Vector3d) normal, const ccls(IMaterial) material);
void Plane_destroy(ccls(Plane) self);
bool Plane_intersect(const ccls(Plane) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord)* hit);
ccls(AABB) Plane_getBoundingBox(const ccls(Plane) self);

EXTERN_POSTFIX
#endif // CAPI_TRACER_SHAPES_PLANE_H