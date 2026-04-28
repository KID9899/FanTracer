//
// Created by iliya on 4/23/26.
//

#include "matrix3d.h"

AllowCopyImpl(Matrix3d);
AllowMoveImpl(Matrix3d);
DestructorImpl(Matrix3d);

Matrix3d::Matrix3d(__m128 col0, __m128 col1, __m128 col2): col0(col0), col1(col1), col2(col2) {}
Matrix3d::Matrix3d(): col0(_mm_set1_ps(0.f)), col1(_mm_set1_ps(0.f)), col2(_mm_set1_ps(0.f)) {}

Matrix3d Matrix3d::concatCols(Float3 col0, Float3 col1, Float3 col2) {
    return Matrix3d(
        _mm_set_ps(0.f, col0.z, col0.y, col0.x),
        _mm_set_ps(0.f, col1.z, col1.y, col1.x),
        _mm_set_ps(0.f, col2.z, col2.y, col2.x)
    );
}
Matrix3d Matrix3d::concatRows(Float3 row0, Float3 row1, Float3 row2) {
    return Matrix3d(
        _mm_set_ps(0.f, row2.x, row1.x, row0.x),
        _mm_set_ps(0.f, row2.y, row1.y, row0.y),
        _mm_set_ps(0.f, row2.z, row1.z, row0.z)
    );
}

Matrix3d Matrix3d::eye() { return concatRows({1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}); }
Matrix3d Matrix3d::diag(float x) { return concatRows({x, 0.f, 0.f}, {0.f, x, 0.f}, {0.f, 0.f, x}); }
Matrix3d Matrix3d::fill(float x) { return concatRows({x, x, x}, {x, x, x}, {x, x, x}); }

Matrix3d Matrix3d::unsafeCreateFromXMM(__m128 col0, __m128 col1, __m128 col2) { return Matrix3d(col0, col1, col2); }

Matrix3d &Matrix3d::operator+=(const Matrix3d &other) {
    col0 = _mm_add_ps(col0, other.col0);
    col1 = _mm_add_ps(col1, other.col1);
    col2 = _mm_add_ps(col2, other.col2);
    return *this;
}
Matrix3d &Matrix3d::operator-=(const Matrix3d &other) {
    col0 = _mm_sub_ps(col0, other.col0);
    col1 = _mm_sub_ps(col1, other.col1);
    col2 = _mm_sub_ps(col2, other.col2);
    return *this;
}
Matrix3d &Matrix3d::operator*=(const Matrix3d &other) {
    col0 = _mm_mul_ps(col0, other.col0);
    col1 = _mm_mul_ps(col1, other.col1);
    col2 = _mm_mul_ps(col2, other.col2);
    return *this;
}
Matrix3d &Matrix3d::operator/=(const Matrix3d &other) {
    col0 = _mm_div_ps(col0, other.col0);
    col1 = _mm_div_ps(col1, other.col1);
    col2 = _mm_div_ps(col2, other.col2);
    return *this;
}

Matrix3d &Matrix3d::operator*=(float other) {
    __m128 vector = _mm_set1_ps(other);
    col0 = _mm_mul_ps(col0, vector);
    col1 = _mm_mul_ps(col1, vector);
    col2 = _mm_mul_ps(col2, vector);
    return *this;
}
Matrix3d &Matrix3d::operator/=(float other) {
    __m128 vector = _mm_set1_ps(other);
    col0 = _mm_div_ps(col0, vector);
    col1 = _mm_div_ps(col1, vector);
    col2 = _mm_div_ps(col2, vector);
    return *this;
}

Vector3d Matrix3d::apply(const Vector3d &v) const {
    __m128 vx = _mm_shuffle_ps(v.getData(), v.getData(), _MM_SHUFFLE(0,0,0,0));
    __m128 vy = _mm_shuffle_ps(v.getData(), v.getData(), _MM_SHUFFLE(1,1,1,1));
    __m128 vz = _mm_shuffle_ps(v.getData(), v.getData(), _MM_SHUFFLE(2,2,2,2));
    __m128 res = _mm_add_ps(
            _mm_mul_ps(col0, vx),
        _mm_add_ps(
            _mm_mul_ps(col1, vy),
            _mm_mul_ps(col2, vz)
        )
    );
    return Vector3d::unsafeCreateFromXMM(res);
}
Vector3d operator^(const Matrix3d& m, const Vector3d& v) noexcept {
    return m.apply(v);
}

DefaultBinOpImpl(Matrix3d, +);
DefaultBinOpImpl(Matrix3d, -);
DefaultBinOpImpl(Matrix3d, *);
DefaultBinOpImpl(Matrix3d, /);

LeftBinOpImpl(Matrix3d, float, *);
LeftBinOpImpl(Matrix3d, float, /);

CommutativeOpImpl(Matrix3d, Matrix3d, float, *);
