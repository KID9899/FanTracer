//
// Created by iliya on 4/26/26.
//

#include "shape.h"
#include "tracer/all.h"

void IShape_destroy(ccls(IShape) self) {
    delete _tocpp(IShape, self);
}

bool IShape_intersect(const ccls(IShape) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord) *hit) {
    HitRecord h;
    bool res = _tocppc(IShape, self)->intersect(_tocppci(Ray, ray), t_min, t_max, h);
    *hit = _rvtoc(HitRecord, h);
    return res;
}

ccls(AABB) IShape_getBoundingBox(const ccls(IShape) self) {
    return _rvtoc(AABB, _tocppc(IShape, self)->getBoundingBox());
}
