//
// Created by iliya on 4/26/26.
//

#include "sphere.h"
#include "tracer/all.h"

ccls(IShape) Sphere2IShape(ccls(Sphere) obj) {
    auto real_cast = dynamic_cast<IShape*>(_tocpp(Sphere, obj));
    return _toc(IShape, real_cast);
}
ccls(Sphere) IShape2Sphere(ccls(IShape) obj) {
    auto real_cast = dynamic_cast<Sphere*>(_tocpp(IShape, obj));
    return _toc(Sphere, real_cast);
}
const ccls(IShape) const_Sphere2IShape(const ccls(Sphere) obj) {
    auto real_cast = dynamic_cast<const IShape*>(_tocppc(Sphere, obj));
    return _tocc(IShape, real_cast);
}
const ccls(Sphere) const_IShape2Sphere(const ccls(IShape) obj) {
    auto real_cast = dynamic_cast<const Sphere*>(_tocppc(IShape, obj));
    return _tocc(Sphere, real_cast);
}

ccls(Sphere) Sphere_make(const ccls(Vector3d) center, float radius, const ccls(IMaterial) material) {
    return _toc(Sphere, new Sphere(_tocppci(Vector3d, center), radius, _tocppc(IMaterial, material)));
}
void Sphere_destroy(ccls(Sphere) self) {
    delete _tocpp(Sphere, self);
}

bool Sphere_intersect(const ccls(Sphere) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord)* hit) {
    return IShape_intersect(const_Sphere2IShape(self), ray, t_min, t_max, hit);
}
ccls(AABB) Sphere_getBoundingBox(const ccls(Sphere) self) {
    return IShape_getBoundingBox(const_Sphere2IShape(self));
}