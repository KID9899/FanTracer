//
// Created by iliya on 4/26/26.
//

#include "sky_light.h"
#include "tracer/all.h"

ccls(ILight) SkyLight2ILight(ccls(SkyLight) obj) {
    auto real_cast = dynamic_cast<ILight*>(_tocpp(SkyLight, obj));
    return _toc(ILight, real_cast);
}
ccls(SkyLight) ILight2SkyLight(ccls(ILight) obj) {
    auto real_cast = dynamic_cast<SkyLight*>(_tocpp(ILight, obj));
    return _toc(SkyLight, real_cast);
}
const ccls(ILight) const_SkyLight2ILight(const ccls(SkyLight) obj) {
    auto real_cast = dynamic_cast<const ILight*>(_tocppc(SkyLight, obj));
    return _tocc(ILight, real_cast);
}
const ccls(SkyLight) const_ILight2SkyLight(const ccls(ILight) obj) {
    auto real_cast = dynamic_cast<const SkyLight*>(_tocppc(ILight, obj));
    return _tocc(SkyLight, real_cast);
}

ccls(SkyLight) SkyLight_make(const ccls(Vector3d) intensity) {
    return _toc(SkyLight, new SkyLight(_tocppci(Vector3d, intensity)));
}
void SkyLight_destroy(ccls(SkyLight) self) {
    delete _tocpp(SkyLight, self);
}

ccls(Vector3d) SkyLight_illuminate(const ccls(SkyLight) self, const ccls(HitRecord) hit, ccls(Vector3d)* light_dir, float* distance) {
    return ILight_illuminate(const_SkyLight2ILight(self), hit, light_dir, distance);
}
ccls(Vector3d) SkyLight_samplePoint(const ccls(SkyLight) self) {
    return ILight_samplePoint(const_SkyLight2ILight(self));
}
