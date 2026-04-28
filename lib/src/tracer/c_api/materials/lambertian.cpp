//
// Created by iliya on 4/26/26.
//

#include "lambertian.h"
#include "tracer/all.h"

ccls(IMaterial) Lambertian2IMaterial(ccls(Lambertian) obj) {
    auto real_cast = dynamic_cast<IMaterial*>(_tocpp(Lambertian, obj));
    return _toc(IMaterial, real_cast);
}
ccls(Lambertian) IMaterial2Lambertian(ccls(IMaterial) obj) {
    auto real_cast = dynamic_cast<Lambertian*>(_tocpp(IMaterial, obj));
    return _toc(Lambertian, real_cast);
}
const ccls(IMaterial) const_Lambertian2IMaterial(const ccls(Lambertian) obj) {
    auto real_cast = dynamic_cast<const IMaterial*>(_tocppc(Lambertian, obj));
    return _tocc(IMaterial, real_cast);
}
const ccls(Lambertian) const_IMaterial2Lambertian(const ccls(IMaterial) obj) {
    auto real_cast = dynamic_cast<const Lambertian*>(_tocppc(IMaterial, obj));
    return _tocc(Lambertian, real_cast);
}

ccls(Lambertian) Lambertian_make(const ccls(Vector3d) color) {
    return _toc(Lambertian, new Lambertian(_tocppci(Vector3d, color)));
}
void Lambertian_destroy(ccls(Lambertian) self) {
    delete _tocpp(Lambertian, self);
}

bool Lambertian_scatter(const ccls(Lambertian) self, const ccls(Ray) in, const ccls(HitRecord) hit, ccls(Vector3d)* absorption_attenuation, ccls(Vector3d)* distortion_attenuation, ccls(Ray)* scattered) {
    return IMaterial_scatter(const_Lambertian2IMaterial(self), in, hit, absorption_attenuation, distortion_attenuation, scattered);
}
ccls(Vector3d) Lambertian_emitted(const ccls(Lambertian) self, const ccls(HitRecord) hit) {
    return IMaterial_emitted(const_Lambertian2IMaterial(self), hit);
}