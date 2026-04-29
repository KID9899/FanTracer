//
// Created by iliya on 4/26/26.
//

#include "vector3d.h"
#include "tracer/all.h"

ccls(Vector3d) Vector3d_copy(const ccls(Vector3d) copy) {
    return _toc(Vector3d, new Vector3d(_tocppci(Vector3d, copy)));
}
ccls(Vector3d) Vector3d_make(float x, float y, float z) {
    return _toc(Vector3d, new Vector3d(x, y, z));
}
ccls(Vector3d) Vector3d_fill(float fill) {
    return _toc(Vector3d, new Vector3d(fill));
}
ccls(Vector3d) Vector3d_empty() {
    return _toc(Vector3d, new Vector3d());
}
ccls(Vector3d) Vector3d_from_f3(const ccls(Float3) f3) {
    return _toc(Vector3d, new Vector3d(_tocppci(Float3, f3)));
}
ccls(Vector3d) Vector3d_unsafeCreateFromXMM(__m128 data) {
    return _rvtoc(Vector3d, Vector3d::unsafeCreateFromXMM(data));
}

void Vector3d_destroy(ccls(Vector3d) self) {
    delete _tocpp(Vector3d, self);
};

float Vector3d_getX(const ccls(Vector3d) self) {
    return _tocppc(Vector3d, self)->getX();
}
float Vector3d_getY(const ccls(Vector3d) self) {
    return _tocppc(Vector3d, self)->getY();
}
float Vector3d_getZ(const ccls(Vector3d) self) {
    return _tocppc(Vector3d, self)->getZ();
}
__m128 Vector3d_getData(const ccls(Vector3d) self) {
    return _tocppc(Vector3d, self)->getData();
}

ccls(Vector3d) Vector3d_replaceX(const ccls(Vector3d) self, float newX) {
    return _rvtoc(Vector3d, _tocppc(Vector3d, self)->replaceX(newX));
}
ccls(Vector3d) Vector3d_replaceY(const ccls(Vector3d) self, float newY) {
    return _rvtoc(Vector3d, _tocppc(Vector3d, self)->replaceY(newY));
}
ccls(Vector3d) Vector3d_replaceZ(const ccls(Vector3d) self, float newZ) {
    return _rvtoc(Vector3d, _tocppc(Vector3d, self)->replaceZ(newZ));
}

float Vector3d_dot(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _tocppc(Vector3d, self)->dot(_tocppci(Vector3d, other));
}
float Vector3d_dotXY(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _tocppc(Vector3d, self)->dotXY(_tocppci(Vector3d, other));
}
float Vector3d_dotXZ(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _tocppc(Vector3d, self)->dotXZ(_tocppci(Vector3d, other));
}
float Vector3d_dotYZ(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _tocppc(Vector3d, self)->dotYZ(_tocppci(Vector3d, other));
}


ccls(Vector3d) Vector3d_add_assign(ccls(Vector3d) self, const ccls(Vector3d) other) {
    _tocpp(Vector3d, self)->operator+=(_tocppci(Vector3d, other));
    return self;
}
ccls(Vector3d) Vector3d_sub_assign(ccls(Vector3d) self, const ccls(Vector3d) other) {
    _tocpp(Vector3d, self)->operator-=(_tocppci(Vector3d, other));
    return self;
}
ccls(Vector3d) Vector3d_mul_assign(ccls(Vector3d) self, const ccls(Vector3d) other) {
    _tocpp(Vector3d, self)->operator*=(_tocppci(Vector3d, other));
    return self;
}
ccls(Vector3d) Vector3d_div_assign(ccls(Vector3d) self, const ccls(Vector3d) other) {
    _tocpp(Vector3d, self)->operator/=(_tocppci(Vector3d, other));
    return self;
}

ccls(Vector3d) Vector3d_smul_assign(ccls(Vector3d) self, float scalar) {
    _tocpp(Vector3d, self)->operator*=(scalar);
    return self;
}
ccls(Vector3d) Vector3d_sdiv_assign(ccls(Vector3d) self, float scalar) {
    _tocpp(Vector3d, self)->operator/=(scalar);
    return self;
}

ccls(Vector3d) Vector3d_neg(const ccls(Vector3d) self) {
    return _rvtoc(Vector3d, _tocppc(Vector3d, self)->operator-());
}

ccls(Vector3d) Vector3d_and_assign(ccls(Vector3d) self, const ccls(Vector3d) other) {
    _tocpp(Vector3d, self)->operator&=(_tocppci(Vector3d, other));
    return self;
}
ccls(Vector3d) Vector3d_or_assign(ccls(Vector3d) self, const ccls(Vector3d) other) {
    _tocpp(Vector3d, self)->operator|=(_tocppci(Vector3d, other));
    return self;
}


float Vector3d_hypot(const ccls(Vector3d) self) {
    return _tocppc(Vector3d, self)->hypot();
}
float Vector3d_length(const ccls(Vector3d) self) {
    return _tocppc(Vector3d, self)->length();
}


float Vector3d_max(const ccls(Vector3d) self) {
    return _tocppc(Vector3d, self)->max();
}
float Vector3d_min(const ccls(Vector3d) self) {
    return _tocppc(Vector3d, self)->min();
}

ccls(Vector3d) Vector3d_abs(const ccls(Vector3d) self) {
    return _rvtoc(Vector3d, _tocppc(Vector3d, self)->abs());
}
ccls(Vector3d) Vector3d_sign(const ccls(Vector3d) self) {
    return _rvtoc(Vector3d, _tocppc(Vector3d, self)->sign());
}
ccls(Vector3d) Vector3d_normalize(const ccls(Vector3d) self) {
    return _rvtoc(Vector3d, _tocppc(Vector3d, self)->normalize());
}

ccls(Vector3d) Vector3d_cross(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(Vector3d, _tocppc(Vector3d, self)->cross(_tocppci(Vector3d, other)));
}


ccls(Vector3d) Vector3d_add(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(Vector3d, _tocppci(Vector3d, self) + _tocppci(Vector3d, other));
}
ccls(Vector3d) Vector3d_sub(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(Vector3d, _tocppci(Vector3d, self) - _tocppci(Vector3d, other));
}
ccls(Vector3d) Vector3d_mul(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(Vector3d, _tocppci(Vector3d, self) * _tocppci(Vector3d, other));
}
ccls(Vector3d) Vector3d_div(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(Vector3d, _tocppci(Vector3d, self) / _tocppci(Vector3d, other));
}

ccls(Vector3d) Vector3d_smul(const ccls(Vector3d) self, float scalar) {
    return _rvtoc(Vector3d, _tocppci(Vector3d, self) * scalar);
}
ccls(Vector3d) Vector3d_sdiv(const ccls(Vector3d) self, float scalar) {
    return _rvtoc(Vector3d, _tocppci(Vector3d, self) / scalar);
}

ccls(Vector3d) Vector3d_and(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(Vector3d, _tocppci(Vector3d, self) & _tocppci(Vector3d, other));
}
ccls(Vector3d) Vector3d_or(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(Vector3d, _tocppci(Vector3d, self) | _tocppci(Vector3d, other));
}


ccls(LogicalMask3d) Vector3d_eq(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) == _tocppci(Vector3d, other));
}
ccls(LogicalMask3d) Vector3d_gt(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) > _tocppci(Vector3d, other));
}
ccls(LogicalMask3d) Vector3d_lt(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) < _tocppci(Vector3d, other));
}
ccls(LogicalMask3d) Vector3d_ge(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) >= _tocppci(Vector3d, other));
}
ccls(LogicalMask3d) Vector3d_le(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) <= _tocppci(Vector3d, other));
}
ccls(LogicalMask3d) Vector3d_neq(const ccls(Vector3d) self, const ccls(Vector3d) other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) != _tocppci(Vector3d, other));
}

ccls(LogicalMask3d) Vector3d_seq(const ccls(Vector3d) self, float other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) == other);
}
ccls(LogicalMask3d) Vector3d_sgt(const ccls(Vector3d) self, float other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) > other);
}
ccls(LogicalMask3d) Vector3d_slt(const ccls(Vector3d) self, float other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) < other);
}
ccls(LogicalMask3d) Vector3d_sge(const ccls(Vector3d) self, float other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) >= other);
}
ccls(LogicalMask3d) Vector3d_sle(const ccls(Vector3d) self, float other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) <= other);
}
ccls(LogicalMask3d) Vector3d_sneq(const ccls(Vector3d) self, float other) {
    return _rvtoc(LogicalMask3d, _tocppci(Vector3d, self) != other);
}

ccls(LogicalMask3d) Vector3d_toMask(const ccls(Vector3d) self) {
    return _rvtoc(LogicalMask3d, _tocppc(Vector3d, self)->toMask());
}
