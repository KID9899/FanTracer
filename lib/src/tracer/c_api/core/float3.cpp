//
// Created by iliya on 4/26/26.
//

#include "float3.h"
#include "tracer/core.h"

ccls(Float3) Float3_make(float x, float y, float z) {
    return _toc(Float3, (new Float3{x, y, z}));
}
ccls(Float3) Float3_empty() {
    return _toc(Float3, (new Float3{0.f, 0.f, 0.f}));
}
void Float3_destroy(ccls(Float3) self) {
    delete _tocpp(Float3, self);
}

float Float3_x(const ccls(Float3) self) {
    return _tocppc(Float3, self)->x;
}
float Float3_y(const ccls(Float3) self) {
    return _tocppc(Float3, self)->y;
}
float Float3_z(const ccls(Float3) self) {
    return _tocppc(Float3, self)->z;
}

void Float3_set_x(ccls(Float3) self, float x) {
    _tocpp(Float3, self)->x = x;
}
void Float3_set_y(ccls(Float3) self, float y) {
    _tocpp(Float3, self)->y = y;
}
void Float3_set_z(ccls(Float3) self, float z) {
    _tocpp(Float3, self)->z = z;
}
