//
// Created by iliya on 4/26/26.
//

#include "orientedbox.h"
#include "tracer/all.h"

ccls(IShape) OrientedBox2IShape(ccls(OrientedBox) obj) {
    auto real_cast = dynamic_cast<IShape*>(_tocpp(OrientedBox, obj));
    return _toc(IShape, real_cast);
}
ccls(OrientedBox) IShape2OrientedBox(ccls(IShape) obj) {
    auto real_cast = dynamic_cast<OrientedBox*>(_tocpp(IShape, obj));
    return _toc(OrientedBox, real_cast);
}
const ccls(IShape) const_OrientedBox2IShape(const ccls(OrientedBox) obj) {
    auto real_cast = dynamic_cast<const IShape*>(_tocppc(OrientedBox, obj));
    return _tocc(IShape, real_cast);
}
const ccls(OrientedBox) const_IShape2OrientedBox(const ccls(IShape) obj) {
    auto real_cast = dynamic_cast<const OrientedBox*>(_tocppc(IShape, obj));
    return _tocc(OrientedBox, real_cast);
}

ccls(OrientedBox) OrientedBox_make(const ccls(Vector3d) center, const ccls(Vector3d) size, const ccls(Float3) rot, const ccls(IMaterial) material) {
    return _toc(OrientedBox, new OrientedBox(_tocppci(Vector3d, center), _tocppci(Vector3d, size), _tocppci(Float3, rot), _tocppc(IMaterial, material)));
}
void OrientedBox_destroy(ccls(OrientedBox) self) {
    delete _tocpp(OrientedBox, self);
}

bool OrientedBox_intersect(const ccls(OrientedBox) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord) *hit) {
    return IShape_intersect(const_OrientedBox2IShape(self), ray, t_min, t_max, hit);
}
ccls(AABB) OrientedBox_getBoundingBox(const ccls(OrientedBox) self) {
    return IShape_getBoundingBox(const_OrientedBox2IShape(self));
}
