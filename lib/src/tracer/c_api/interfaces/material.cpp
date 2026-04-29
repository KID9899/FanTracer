//
// Created by iliya on 4/26/26.
//

#include "material.h"
#include "tracer/all.h"

void IMaterial_destroy(ccls(IMaterial) self) {
    delete _tocpp(IMaterial, self);
}

bool IMaterial_scatter(const ccls(IMaterial) self, const ccls(Ray) in, const ccls(HitRecord) hit, ccls(Vector3d) *absorption_attenuation, ccls(Vector3d) *distortion_attenuation, ccls(Ray) *scattered) {
    Vector3d abs, dis;
    Ray scat;
    bool res = _tocppc(IMaterial, self)->scatter(_tocppci(Ray, in), _tocppci(HitRecord, hit), abs, dis, scat);
    *absorption_attenuation = _rvtoc(Vector3d, abs);
    *distortion_attenuation = _rvtoc(Vector3d, dis);
    *scattered = _rvtoc(Ray, scat);
    return res;
}

ccls(Vector3d) IMaterial_emitted(const ccls(IMaterial) self, const ccls(HitRecord) hit) {
    return _rvtoc(Vector3d, _tocppc(IMaterial, self)->emitted(_tocppci(HitRecord, hit)));
}
