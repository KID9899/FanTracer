//
// Created by iliya on 4/26/26.
//

#include "hit_record.h"
#include "tracer/structs.h"

ccls(HitRecord) HitRecord_empty() {
    return _toc(HitRecord, new HitRecord);
}
ccls(HitRecord) HitRecord_copy(const ccls(HitRecord) other) {
    return _toc(HitRecord, new HitRecord(_tocppci(HitRecord, other)));
}
void HitRecord_destroy(ccls(HitRecord) self) {
    delete _tocpp(HitRecord, self);
}

const float HitRecord_get_t(const ccls(HitRecord) self) {
    return _tocppc(HitRecord, self)->t;
}
void HitRecord_set_t(ccls(HitRecord) self, float t) {
    _tocpp(HitRecord, self)->t = t;
}

const ccls(Vector3d) HitRecord_get_point(const ccls(HitRecord) self) {
    return _rvtoc(Vector3d, _tocppc(HitRecord, self)->point);
}
void HitRecord_set_point(ccls(HitRecord) self, const ccls(Vector3d) point) {
    _tocpp(HitRecord, self)->point = _tocppci(Vector3d, point);
}

const ccls(Vector3d) HitRecord_get_normal(const ccls(HitRecord) self) {
    return _rvtoc(Vector3d, _tocppc(HitRecord, self)->normal);
}
void HitRecord_set_normal(ccls(HitRecord) self, const ccls(Vector3d) normal) {
    _tocpp(HitRecord, self)->normal = _tocppci(Vector3d, normal);
}

const ccls(IMaterial) HitRecord_get_material(const ccls(HitRecord) self) {
    return _tocc(IMaterial, _tocppc(HitRecord, self)->material);
}
void HitRecord_set_material(ccls(HitRecord) self, const ccls(IMaterial) material) {
    _tocpp(HitRecord, self)->material = _tocppc(IMaterial, material);
}

const bool HitRecord_get_frontFace(const ccls(HitRecord) self) {
    return _tocppc(HitRecord, self)->frontFace;
}
void HitRecord_set_frontFace(ccls(HitRecord) self, bool frontFace) {
    _tocpp(HitRecord, self)->frontFace = frontFace;
}
