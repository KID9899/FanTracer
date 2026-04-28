//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"

#ifndef CAPI_TRACER_SHAPES_CYLINDER_H
#define CAPI_TRACER_SHAPES_CYLINDER_H
EXTERN_PREFIX

make_capi(Cylinder);

ccls(IShape) Cylinder2IShape(ccls(Cylinder) obj);
ccls(Cylinder) IShape2Cylinder(ccls(IShape) obj);
const ccls(IShape) const_Cylinder2IShape(const ccls(Cylinder) obj);
const ccls(Cylinder) const_IShape2Cylinder(const ccls(IShape) obj);

ccls(Cylinder) Cylinder_make(const ccls(Vector3d) center, float radius, float height, const ccls(Float3) rot, const ccls(IMaterial) material);
void Cylinder_destroy(ccls(Cylinder) self);
bool Cylinder_intersect(const ccls(Cylinder) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord)* hit);
ccls(AABB) Cylinder_getBoundingBox(const ccls(Cylinder) self);

EXTERN_POSTFIX
#endif // CAPI_TRACER_SHAPES_CYLINDER_H