//
// Created by iliya on 4/26/26.
//

#include "mirror.h"
#include "tracer/all.h"

ccls(IMaterial) Mirror2IMaterial(ccls(Mirror) obj) {
    auto real_cast = dynamic_cast<IMaterial*>(_tocpp(Mirror, obj));
    return _toc(IMaterial, real_cast);
}
ccls(Mirror) IMaterial2Mirror(ccls(IMaterial) obj) {
    auto real_cast = dynamic_cast<Mirror*>(_tocpp(IMaterial, obj));
    return _toc(Mirror, real_cast);
}
const ccls(IMaterial) const_Mirror2IMaterial(const ccls(Mirror) obj) {
    auto real_cast = dynamic_cast<const IMaterial*>(_tocppc(Mirror, obj));
    return _tocc(IMaterial, real_cast);
}
const ccls(Mirror) const_IMaterial2Mirror(const ccls(IMaterial) obj) {
    auto real_cast = dynamic_cast<const Mirror*>(_tocppc(IMaterial, obj));
    return _tocc(Mirror, real_cast);
}

ccls(Mirror) Mirror_make(const ccls(Vector3d) albedo, float fuzz) {
    return _toc(Mirror, new Mirror(_tocppci(Vector3d, albedo), fuzz));
}
void Mirror_destroy(ccls(Mirror) self) {
    delete _tocpp(Mirror, self);
}

bool Mirror_scatter(const ccls(Mirror) self, const ccls(Ray) in, const ccls(HitRecord) hit, ccls(Vector3d) *absorption_attenuation, ccls(Vector3d) *distortion_attenuation, ccls(Ray) *scattered) {
    return IMaterial_scatter(const_Mirror2IMaterial(self), in, hit, absorption_attenuation, distortion_attenuation, scattered);
}
ccls(Vector3d) Mirror_emitted(const ccls(Mirror) self, const ccls(HitRecord) hit) {
    return IMaterial_emitted(const_Mirror2IMaterial(self), hit);
}
