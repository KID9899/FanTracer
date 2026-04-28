//
// Created by iliya on 4/26/26.
//

#include "cylinder.h"
#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"
#include "tracer/shapes.h"

ccls(IShape) Cylinder2IShape(ccls(Cylinder) obj) {
    auto real_cast = dynamic_cast<IShape*>(_tocpp(Cylinder, obj));
    return _toc(IShape, real_cast);
}
ccls(Cylinder) IShape2Cylinder(ccls(IShape) obj) {
    auto real_cast = dynamic_cast<Cylinder*>(_tocpp(IShape, obj));
    return _toc(Cylinder, real_cast);
}
const ccls(IShape) const_Cylinder2IShape(const ccls(Cylinder) obj) {
    auto real_cast = dynamic_cast<const IShape*>(_tocppc(Cylinder, obj));
    return _tocc(IShape, real_cast);
}
const ccls(Cylinder) const_IShape2Cylinder(const ccls(IShape) obj) {
    auto real_cast = dynamic_cast<const Cylinder*>(_tocppc(IShape, obj));
    return _tocc(Cylinder, real_cast);
}

ccls(Cylinder) Cylinder_make(const ccls(Vector3d) center, float radius, float height, const ccls(Float3) rot, const ccls(IMaterial) material) {
    return _toc(Cylinder, new Cylinder(_tocppci(Vector3d, center), radius, height, _tocppci(Float3, rot), _tocppc(IMaterial, material)));
}
void Cylinder_destroy(ccls(Cylinder) self) {
    delete _tocpp(Cylinder, self);
}

bool Cylinder_intersect(const ccls(Cylinder) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord)* hit) {
    return IShape_intersect(const_Cylinder2IShape(self), ray, t_min, t_max, hit);
}
ccls(AABB) Cylinder_getBoundingBox(const ccls(Cylinder) self) {
    return IShape_getBoundingBox(const_Cylinder2IShape(self));
}
