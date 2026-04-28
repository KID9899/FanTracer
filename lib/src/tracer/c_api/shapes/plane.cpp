//
// Created by iliya on 4/26/26.
//

#include "plane.h"
#include "tracer/all.h"

ccls(IShape) Plane2IShape(ccls(Plane) obj) {
    auto real_cast = dynamic_cast<IShape*>(_tocpp(Plane, obj));
    return _toc(IShape, real_cast);
}
ccls(Plane) IShape2Plane(ccls(IShape) obj) {
    auto real_cast = dynamic_cast<Plane*>(_tocpp(IShape, obj));
    return _toc(Plane, real_cast);
}
const ccls(IShape) const_Plane2IShape(const ccls(Plane) obj) {
    auto real_cast = dynamic_cast<const IShape*>(_tocppc(Plane, obj));
    return _tocc(IShape, real_cast);
}
const ccls(Plane) const_IShape2Plane(const ccls(IShape) obj) {
    auto real_cast = dynamic_cast<const Plane*>(_tocppc(IShape, obj));
    return _tocc(Plane, real_cast);
}

ccls(Plane) Plane_make(const ccls(Vector3d) point, const ccls(Vector3d) normal, const ccls(IMaterial) material) {
    return _toc(Plane, new Plane(_tocppci(Vector3d, point), _tocppci(Vector3d, normal), _tocppc(IMaterial, material)));
}
void Plane_destroy(ccls(Plane) self) {
    delete _tocpp(Plane, self);
}

bool Plane_intersect(const ccls(Plane) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord)* hit) {
    return IShape_intersect(const_Plane2IShape(self), ray, t_min, t_max, hit);
}
ccls(AABB) Plane_getBoundingBox(const ccls(Plane) self) {
    return IShape_getBoundingBox(const_Plane2IShape(self));
}