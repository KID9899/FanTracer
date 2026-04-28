//
// Created by iliya on 4/26/26.
//

#include "logicalmask3d.h"
#include "tracer/core.h"

ccls(LogicalMask3d) LogicalMask3d_empty() {
    return _toc(LogicalMask3d, new LogicalMask3d());
}
ccls(LogicalMask3d) LogicalMask3d_copy(const ccls(LogicalMask3d) copy) {
    return _toc(LogicalMask3d, new LogicalMask3d(_tocppci(LogicalMask3d, copy)));
}
void LogicalMask3d_destroy(ccls(LogicalMask3d) self) {
    delete _tocpp(LogicalMask3d, self);
}

bool LogicalMask3d_x(const ccls(LogicalMask3d) self) {
    return _tocppc(LogicalMask3d, self)->x();
}
bool LogicalMask3d_y(const ccls(LogicalMask3d) self) {
    return _tocppc(LogicalMask3d, self)->y();
}
bool LogicalMask3d_z(const ccls(LogicalMask3d) self) {
    return _tocppc(LogicalMask3d, self)->z();
}

bool LogicalMask3d_any(const ccls(LogicalMask3d) self) {
    return _tocppc(LogicalMask3d, self)->any();
}
bool LogicalMask3d_all(const ccls(LogicalMask3d) self) {
    return _tocppc(LogicalMask3d, self)->all();
}

ccls(LogicalMask3d) LogicalMask3d_and(const ccls(LogicalMask3d) self, const ccls(LogicalMask3d) other) {
    return _rvtoc(LogicalMask3d, _tocppci(LogicalMask3d, self) && _tocppci(LogicalMask3d, other));
}
ccls(LogicalMask3d) LogicalMask3d_or(const ccls(LogicalMask3d) self, const ccls(LogicalMask3d) other) {
    return _rvtoc(LogicalMask3d, _tocppci(LogicalMask3d, self) || _tocppci(LogicalMask3d, other));
}
ccls(LogicalMask3d) LogicalMask3d_xor(const ccls(LogicalMask3d) self, const ccls(LogicalMask3d) other) {
    return _rvtoc(LogicalMask3d, _tocppci(LogicalMask3d, self) ^ _tocppci(LogicalMask3d, other));
}
ccls(LogicalMask3d) LogicalMask3d_not(const ccls(LogicalMask3d) self) {
    return _rvtoc(LogicalMask3d, !_tocppci(LogicalMask3d, self));
}

ccls(Vector3d) LogicalMask3d_assign(const ccls(LogicalMask3d) self, const ccls(Vector3d) other) {
    return _rvtoc(Vector3d, _tocppci(LogicalMask3d, self) * _tocppci(Vector3d, other));
}
ccls(Vector3d) LogicalMask3d_combine(const ccls(LogicalMask3d) self, const ccls(Vector3d) true_v, const ccls(Vector3d) false_v) {
    return _rvtoc(Vector3d, _tocppci(LogicalMask3d, self).combine(_tocppci(Vector3d, true_v), _tocppci(Vector3d, false_v)));
}

char LogicalMask3d_toChar(const ccls(LogicalMask3d) self) {
    return _tocppc(LogicalMask3d, self)->toChar();
}
ccls(Vector3d) LogicalMask3d_toVector(const ccls(LogicalMask3d) self) {
    return _rvtoc(Vector3d, _tocppc(LogicalMask3d, self)->toVector());
}
