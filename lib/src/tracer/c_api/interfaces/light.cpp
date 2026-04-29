//
// Created by iliya on 4/26/26.
//

#include "light.h"
#include "tracer/all.h"

void ILight_destroy(ccls(ILight) self) {
    delete _tocpp(ILight, self);
}

ccls(Vector3d) ILight_illuminate(const ccls(ILight) self, const ccls(HitRecord) hit, ccls(Vector3d) *light_dir, float *distance) {
    Vector3d dir;
    float dist;
    Vector3d intensity = _tocppc(ILight, self)->illuminate(_tocppci(HitRecord, hit), dir, dist);

    *light_dir = _rvtoc(Vector3d, dir);
    *distance = dist;
    return _rvtoc(Vector3d, intensity);
}

ccls(Vector3d) ILight_samplePoint(const ccls(ILight) self) {
    return _rvtoc(Vector3d, _tocppc(ILight, self)->samplePoint());
}
