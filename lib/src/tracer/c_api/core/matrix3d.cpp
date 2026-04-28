//
// Created by iliya on 4/26/26.
//

#include "matrix3d.h"
#include "tracer/all.h"

ccls(Matrix3d) Matrix3d_empty() {
    return _toc(Matrix3d, new Matrix3d);
}
ccls(Matrix3d) Matrix3d_concatCols(ccls(Float3) col0, ccls(Float3) col1, ccls(Float3) col2) {
    return _rvtoc(Matrix3d, Matrix3d::concatCols(
            _tocppci(Float3, col0), _tocppci(Float3, col1), _tocppci(Float3, col2)));
}
ccls(Matrix3d) Matrix3d_concatRows(ccls(Float3) row0, ccls(Float3) row1, ccls(Float3) row2) {
    return _rvtoc(Matrix3d, Matrix3d::concatRows(
            _tocppci(Float3, row0), _tocppci(Float3, row1), _tocppci(Float3, row2)));
}
ccls(Matrix3d) Matrix3d_eye() {
    return _rvtoc(Matrix3d, Matrix3d::eye());
}
ccls(Matrix3d) Matrix3d_diag(float x) {
    return _rvtoc(Matrix3d, Matrix3d::diag(x));
}
ccls(Matrix3d) Matrix3d_fill(float x) {
    return _rvtoc(Matrix3d, Matrix3d::fill(x));
}
ccls(Matrix3d) Matrix3d_copy(const ccls(Matrix3d) other) {
    return _toc(Matrix3d, new Matrix3d(_tocppci(Matrix3d, other)));
}
void Matrix3d_destroy(ccls(Matrix3d) self) {
    delete _tocpp(Matrix3d, self);
}

ccls(Matrix3d) Matrix3d_add_assign(ccls(Matrix3d) self, const ccls(Matrix3d) other) {
    _tocpp(Matrix3d, self)->operator+=(_tocppci(Matrix3d, other));
    return self;
}
ccls(Matrix3d) Matrix3d_sub_assign(ccls(Matrix3d) self, const ccls(Matrix3d) other) {
    _tocpp(Matrix3d, self)->operator-=(_tocppci(Matrix3d, other));
    return self;
}
ccls(Matrix3d) Matrix3d_mul_assign(ccls(Matrix3d) self, const ccls(Matrix3d) other) {
    _tocpp(Matrix3d, self)->operator*=(_tocppci(Matrix3d, other));
    return self;
}
ccls(Matrix3d) Matrix3d_div_assign(ccls(Matrix3d) self, const ccls(Matrix3d) other) {
    _tocpp(Matrix3d, self)->operator/=(_tocppci(Matrix3d, other));
    return self;
}
ccls(Matrix3d) Matrix3d_smul_assign(ccls(Matrix3d) self, float scalar) {
    _tocpp(Matrix3d, self)->operator*=(scalar);
    return self;
}
ccls(Matrix3d) Matrix3d_sdiv_assign(ccls(Matrix3d) self, float scalar) {
    _tocpp(Matrix3d, self)->operator/=(scalar);
    return self;
}

ccls(Matrix3d) Matrix3d_add(const ccls(Matrix3d) lhs, const ccls(Matrix3d) rhs) {
    return _rvtoc(Matrix3d, _tocppci(Matrix3d, lhs) + _tocppci(Matrix3d, rhs));
}
ccls(Matrix3d) Matrix3d_sub(const ccls(Matrix3d) lhs, const ccls(Matrix3d) rhs) {
    return _rvtoc(Matrix3d, _tocppci(Matrix3d, lhs) - _tocppci(Matrix3d, rhs));
}
ccls(Matrix3d) Matrix3d_mul(const ccls(Matrix3d) lhs, const ccls(Matrix3d) rhs) {
    return _rvtoc(Matrix3d, _tocppci(Matrix3d, lhs) * _tocppci(Matrix3d, rhs));
}
ccls(Matrix3d) Matrix3d_div(const ccls(Matrix3d) lhs, const ccls(Matrix3d) rhs) {
    return _rvtoc(Matrix3d, _tocppci(Matrix3d, lhs) / _tocppci(Matrix3d, rhs));
}
ccls(Matrix3d) Matrix3d_smul(const ccls(Matrix3d) lhs, float scalar) {
    return _rvtoc(Matrix3d, _tocppci(Matrix3d, lhs) * scalar);
}
ccls(Matrix3d) Matrix3d_sdiv(const ccls(Matrix3d) lhs, float scalar) {
    return _rvtoc(Matrix3d, _tocppci(Matrix3d, lhs) / scalar);
}

ccls(Vector3d) Matrix3d_apply(const ccls(Matrix3d) self, const ccls(Vector3d) v) {
    return _rvtoc(Vector3d, _tocppc(Matrix3d, self)->apply(_tocppci(Vector3d, v)));
}
