//
// Created by iliya on 4/23/26.
//

#include <xmmintrin.h>
#include "vector3d.h"
#include "matrix3d.h"

#pragma once

inline Matrix3d::Matrix3d(__m128 col0, __m128 col1, __m128 col2) noexcept: col0(col0), col1(col1), col2(col2) {}
inline Matrix3d::Matrix3d() noexcept: col0(_mm_set1_ps(0.f)), col1(_mm_set1_ps(0.f)), col2(_mm_set1_ps(0.f)) {}

inline Matrix3d Matrix3d::concatCols(const Float3 &col0, const Float3 &col1, const Float3 &col2) noexcept {
    return Matrix3d(
        _mm_set_ps(0.f, col0.z, col0.y, col0.x),
        _mm_set_ps(0.f, col1.z, col1.y, col1.x),
        _mm_set_ps(0.f, col2.z, col2.y, col2.x)
    );
}
inline Matrix3d Matrix3d::concatRows(const Float3 &row0, const Float3 &row1, const Float3 &row2) noexcept {
    return Matrix3d(
        _mm_set_ps(0.f, row2.x, row1.x, row0.x),
        _mm_set_ps(0.f, row2.y, row1.y, row0.y),
        _mm_set_ps(0.f, row2.z, row1.z, row0.z)
    );
}

inline Matrix3d Matrix3d::eye() noexcept { return concatRows({1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}); }
inline Matrix3d Matrix3d::diag(float x) noexcept { return concatRows({x, 0.f, 0.f}, {0.f, x, 0.f}, {0.f, 0.f, x}); }
inline Matrix3d Matrix3d::fill(float x) noexcept { return concatRows({x, x, x}, {x, x, x}, {x, x, x}); }

inline Matrix3d Matrix3d::unsafeCreateFromXMM(__m128 col0, __m128 col1, __m128 col2) noexcept { return Matrix3d(col0, col1, col2); }

inline Matrix3d &Matrix3d::operator+=(const Matrix3d &other) noexcept {
    col0 = _mm_add_ps(col0, other.col0);
    col1 = _mm_add_ps(col1, other.col1);
    col2 = _mm_add_ps(col2, other.col2);
    return *this;
}
inline Matrix3d &Matrix3d::operator-=(const Matrix3d &other) noexcept {
    col0 = _mm_sub_ps(col0, other.col0);
    col1 = _mm_sub_ps(col1, other.col1);
    col2 = _mm_sub_ps(col2, other.col2);
    return *this;
}
inline Matrix3d &Matrix3d::operator*=(const Matrix3d &other) noexcept {
    col0 = _mm_mul_ps(col0, other.col0);
    col1 = _mm_mul_ps(col1, other.col1);
    col2 = _mm_mul_ps(col2, other.col2);
    return *this;
}
inline Matrix3d &Matrix3d::operator/=(const Matrix3d &other) noexcept {
    col0 = _mm_div_ps(col0, other.col0);
    col1 = _mm_div_ps(col1, other.col1);
    col2 = _mm_div_ps(col2, other.col2);
    return *this;
}

inline Matrix3d &Matrix3d::operator*=(float other) noexcept {
    __m128 vector = _mm_set1_ps(other);
    col0 = _mm_mul_ps(col0, vector);
    col1 = _mm_mul_ps(col1, vector);
    col2 = _mm_mul_ps(col2, vector);
    return *this;
}
inline Matrix3d &Matrix3d::operator/=(float other) noexcept {
    __m128 vector = _mm_set1_ps(other);
    col0 = _mm_div_ps(col0, vector);
    col1 = _mm_div_ps(col1, vector);
    col2 = _mm_div_ps(col2, vector);
    return *this;
}

inline Vector3d Matrix3d::apply(const Vector3d &v) const noexcept {
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
inline Vector3d operator^(const Matrix3d &m, const Vector3d &v) noexcept {
    return m.apply(v);
}

inline DefaultBinOpImpl(Matrix3d, +);
inline DefaultBinOpImpl(Matrix3d, -);
inline DefaultBinOpImpl(Matrix3d, *);
inline DefaultBinOpImpl(Matrix3d, /);

inline LeftBinOpImpl(Matrix3d, float, *);
inline LeftBinOpImpl(Matrix3d, float, /);

inline CommutativeOpImpl(Matrix3d, const Matrix3d&, float, *);
