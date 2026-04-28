//
// Created by iliya on 4/26/26.
//

#include "glass.h"
#include "tracer/all.h"

ccls(IMaterial) Glass2IMaterial(ccls(Glass) obj) {
    auto real_cast = dynamic_cast<IMaterial*>(_tocpp(Glass, obj));
    return _toc(IMaterial, real_cast);
}
ccls(Glass) IMaterial2Glass(ccls(IMaterial) obj) {
    auto real_cast = dynamic_cast<Glass*>(_tocpp(IMaterial, obj));
    return _toc(Glass, real_cast);
}
const ccls(IMaterial) const_Glass2IMaterial(const ccls(Glass) obj) {
    auto real_cast = dynamic_cast<const IMaterial*>(_tocppc(Glass, obj));
    return _tocc(IMaterial, real_cast);
}
const ccls(Glass) const_IMaterial2Glass(const ccls(IMaterial) obj) {
    auto real_cast = dynamic_cast<const Glass*>(_tocppc(IMaterial, obj));
    return _tocc(Glass, real_cast);
}

ccls(Glass) Glass_make(const ccls(Vector3d) color, float refraction_index, float reflection_coeff, float tint_coeff) {
    return _toc(Glass, new Glass(_tocppci(Vector3d, color), refraction_index, reflection_coeff, tint_coeff));
}
void Glass_destroy(ccls(Glass) self) {
    delete _tocpp(Glass, self);
}

bool Glass_scatter(const ccls(Glass) self, const ccls(Ray) in, const ccls(HitRecord) hit, ccls(Vector3d)* absorption_attenuation, ccls(Vector3d)* distortion_attenuation, ccls(Ray)* scattered) {
    return IMaterial_scatter(const_Glass2IMaterial(self), in, hit, absorption_attenuation, distortion_attenuation, scattered);
}
ccls(Vector3d) Glass_emitted(const ccls(Glass) self, const ccls(HitRecord) hit) {
    return IMaterial_emitted(const_Glass2IMaterial(self), hit);
}
