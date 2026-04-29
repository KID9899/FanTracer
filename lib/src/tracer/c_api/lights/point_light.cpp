//
// Created by iliya on 4/26/26.
//

#include "point_light.h"
#include "tracer/all.h"

ccls(ILight) PointLight2ILight(ccls(PointLight) obj) {
    auto real_cast = dynamic_cast<ILight*>(_tocpp(PointLight, obj));
    return _toc(ILight, real_cast);
}
ccls(PointLight) ILight2PointLight(ccls(ILight) obj) {
    auto real_cast = dynamic_cast<PointLight*>(_tocpp(ILight, obj));
    return _toc(PointLight, real_cast);
}
const ccls(ILight) const_PointLight2ILight(const ccls(PointLight) obj) {
    auto real_cast = dynamic_cast<const ILight*>(_tocppc(PointLight, obj));
    return _tocc(ILight, real_cast);
}
const ccls(PointLight) const_ILight2PointLight(const ccls(ILight) obj) {
    auto real_cast = dynamic_cast<const PointLight*>(_tocppc(ILight, obj));
    return _tocc(PointLight, real_cast);
}

ccls(PointLight) PointLight_make(const ccls(Vector3d) position, const ccls(Vector3d) intensity) {
    return _toc(PointLight, new PointLight(_tocppci(Vector3d, position), _tocppci(Vector3d, intensity)));
}
void PointLight_destroy(ccls(PointLight) self) {
    delete _tocpp(PointLight, self);
}

ccls(Vector3d) PointLight_illuminate(const ccls(PointLight) self, const ccls(HitRecord) hit, ccls(Vector3d) *light_dir, float *distance) {
    return ILight_illuminate(const_PointLight2ILight(self), hit, light_dir, distance);
}
ccls(Vector3d) PointLight_samplePoint(const ccls(PointLight) self) {
    return ILight_samplePoint(const_PointLight2ILight(self));
}
