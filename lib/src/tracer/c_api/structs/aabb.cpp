//
// Created by iliya on 4/26/26.
//

#include "aabb.h"
#include "tracer/structs.h"

ccls(AABB) AABB_empty() {
    return _toc(AABB, new AABB);
}
ccls(AABB) AABB_make(const ccls(Vector3d) min, const ccls(Vector3d) max) {
    return _toc(AABB, (new AABB{ _tocppci(Vector3d, min), _tocppci(Vector3d, max) }));
}
ccls(AABB) AABB_copy(const ccls(AABB) other) {
    return _toc(AABB, new AABB(_tocppci(AABB, other)));
}
void AABB_destroy(ccls(AABB) self) {
    delete _tocpp(AABB, self);
}

ccls(Vector3d) AABB_min(const ccls(AABB) self) {
    return _rvtoc(Vector3d, _tocppc(AABB, self)->min);
}
void AABB_set_min(ccls(AABB) self, const ccls(Vector3d) min) {
    _tocpp(AABB, self)->min = _tocppci(Vector3d, min);
}
ccls(Vector3d) AABB_max(const ccls(AABB) self) {
    return _rvtoc(Vector3d, _tocppc(AABB, self)->max);
}
void AABB_set_max(ccls(AABB) self, const ccls(Vector3d) max) {
    _tocpp(AABB, self)->max = _tocppci(Vector3d, max);
}
