//
// Created by iliya on 4/26/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"

#ifndef CAPI_TRACER_SHAPES_ORIENTEDBOX_H
#define CAPI_TRACER_SHAPES_ORIENTEDBOX_H
EXTERN_PREFIX

make_capi(OrientedBox);

ccls(IShape) OrientedBox2IShape(ccls(OrientedBox) obj);
ccls(OrientedBox) IShape2OrientedBox(ccls(IShape) obj);
const ccls(IShape) const_OrientedBox2IShape(const ccls(OrientedBox) obj);
const ccls(OrientedBox) const_IShape2OrientedBox(const ccls(IShape) obj);

ccls(OrientedBox) OrientedBox_make(const ccls(Vector3d) center, const ccls(Vector3d) size, const ccls(Float3) rot, const ccls(IMaterial) material);
void OrientedBox_destroy(ccls(OrientedBox) self);
bool OrientedBox_intersect(const ccls(OrientedBox) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord)* hit);
ccls(AABB) OrientedBox_getBoundingBox(const ccls(OrientedBox) self);

EXTERN_POSTFIX
#endif // CAPI_TRACER_SHAPES_ORIENTEDBOX_H