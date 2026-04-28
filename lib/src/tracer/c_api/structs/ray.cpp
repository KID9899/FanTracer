//
// Created by iliya on 4/26/26.
//

#include "ray.h"
#include "tracer/all.h"

ccls(Ray) Ray_empty() {
    return _toc(Ray, new Ray);
}
ccls(Ray) Ray_make(const ccls(Vector3d) origin, const ccls(Vector3d) direction) {
    return _toc(Ray, (new Ray{ _tocppci(Vector3d, origin), _tocppci(Vector3d, direction) }));
}
ccls(Ray) Ray_copy(const ccls(Ray) other) {
    return _toc(Ray, new Ray(_tocppci(Ray, other)));
}
void Ray_destroy(ccls(Ray) self) {
    delete _tocpp(Ray, self);
}

ccls(Vector3d) Ray_origin(const ccls(Ray) self) {
    return _rvtoc(Vector3d, _tocppc(Ray, self)->origin);
}
ccls(Vector3d) Ray_direction(const ccls(Ray) self) {
    return _rvtoc(Vector3d, _tocppc(Ray, self)->direction);
}
ccls(Vector3d) Ray_at(const ccls(Ray) self, float t) {
    return _rvtoc(Vector3d, _tocppc(Ray, self)->at(t));
}
