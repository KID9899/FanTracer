//
// Created by iliya on 4/18/26.
//

#include <xmmintrin.h>
#include <cmath>
#include "vector3d.h"
#include "logicalmask3d.h"
#include "matrix3d.h"

#ifdef __SSE4_1__
    #include <smmintrin.h>
#endif

AllowCopyImpl(Vector3d);
AllowMoveImpl(Vector3d);
DestructorImpl(Vector3d);

// ================ КОНСТРУКТОРЫ ================
Vector3d::Vector3d(__m128 data) noexcept: data(data) {}
Vector3d::Vector3d(float x, float y, float z) noexcept: data(_mm_set_ps(0.f, z, y, x)) {}
Vector3d::Vector3d(float fill) noexcept: data(_mm_set_ps(0.f, fill, fill, fill)) {}
Vector3d::Vector3d() noexcept: data(_mm_set1_ps(0.f)) {}
Vector3d::Vector3d(const Float3& f3): data(_mm_set_ps(0.f, f3.z, f3.y, f3.x)) {}

Vector3d Vector3d::unsafeCreateFromXMM(__m128 data) noexcept { return Vector3d(data); }

// ================ ГЕТТЕРЫ ================
float Vector3d::getX() const {
    return _mm_cvtss_f32(data);
}
float Vector3d::getY() const {
    __m128 tmp = _mm_shuffle_ps(data, data, _MM_SHUFFLE(1,1,1,1));
    return _mm_cvtss_f32(tmp);
}
float Vector3d::getZ() const {
    __m128 tmp = _mm_shuffle_ps(data, data, _MM_SHUFFLE(2,2,2,2));
    return _mm_cvtss_f32(tmp);
}
__m128 Vector3d::getData() const {
    return data;
}

// ================ СЕТТЕРЫ ================
Vector3d Vector3d::replaceX(float newX) const noexcept {
    __m128 tmp = _mm_move_ss(data, _mm_set_ss(newX));
    return Vector3d(tmp);
}
Vector3d Vector3d::replaceY(float newY) const noexcept {
#ifdef __SSE4_1__
    __m128 tmp = _mm_insert_ps(data, _mm_set_ss(newY), 0x10);
#else
    __m128 vy = _mm_set1_ps(newY);
    __m128 tmp = _mm_or_ps(
            _mm_and_ps(data, _mm_castsi128_ps(_mm_set_epi32(-1, -1,  0, -1))),
            _mm_and_ps(vy,   _mm_castsi128_ps(_mm_set_epi32( 0,  0, -1,  0)))
    );
#endif
    return Vector3d(tmp);
}
Vector3d Vector3d::replaceZ(float newZ) const noexcept {
#ifdef __SSE4_1__
    __m128 tmp = _mm_insert_ps(data, _mm_set_ss(newZ), 0x20);
#else
    __m128 vz = _mm_set1_ps(newZ);
    __m128 tmp = _mm_or_ps(
            _mm_and_ps(data, _mm_castsi128_ps(_mm_set_epi32(-1,  0, -1, -1))),
            _mm_and_ps(vz,   _mm_castsi128_ps(_mm_set_epi32( 0, -1,  0,  0)))
    );
#endif
    return Vector3d(tmp);
}

// ================ СКАЛЯРНЫЕ ПРОИЗВЕДЕНИЯ ================
float Vector3d::dot(const Vector3d& other) const { return dot(other.data); }
float Vector3d::dot(const __m128& other) const {
#ifdef __SSE4_1__
    __m128 tmp = _mm_dp_ps(data, other.data, 0xFF);
    return _mm_cvtss_f32(tmp);
#else
    // dw, cz, by, ax
    __m128 mul = _mm_mul_ps(data, other);

    // cz, dw, ax, by
    __m128 shuf1 = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2,3,0,1));
    // cz+dw, dw+cz, by+ax, ax+by
    __m128 sum1  = _mm_add_ps(mul, shuf1);

    // by+ax, ax+by, cz+dw, dw+cz
    __m128 shuf2 = _mm_shuffle_ps(sum1, sum1, _MM_SHUFFLE(1,0,3,2));
    // cz+dw+by+ax, dw+cz+ax+by, by+ax+cz+dw, ax+by+dw+cz
    __m128 sum2  = _mm_add_ps(sum1, shuf2);

    return _mm_cvtss_f32(sum2);
#endif
}

float Vector3d::dotXY(const Vector3d& other) const { return dotXY(other.data); }
float Vector3d::dotXY(const __m128& other) const {
#ifdef __SSE4_1__
    __m128 tmp = _mm_dp_ps(data, other, 0x3F);
    return _mm_cvtss_f32(tmp);
#else
    __m128 mul = _mm_mul_ps(data, other);
    __m128 shuf_y = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(1, 1, 1, 1));
    __m128 sum_xy = _mm_add_ss(mul, shuf_y);
    return _mm_cvtss_f32(sum_xy);
#endif
}

float Vector3d::dotXZ(const Vector3d& other) const { return dotXZ(other.data); }
float Vector3d::dotXZ(const __m128& other) const {
#ifdef __SSE4_1__
    __m128 tmp = _mm_dp_ps(data, other, 0x5F);
    return _mm_cvtss_f32(tmp);
#else
    __m128 mul = _mm_mul_ps(data, other);
    __m128 shuf_z = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 2, 2, 2));
    __m128 sum_xz = _mm_add_ss(mul, shuf_z);
    return _mm_cvtss_f32(sum_xz);
#endif
}

float Vector3d::dotYZ(const Vector3d& other) const { return dotYZ(other.data); }
float Vector3d::dotYZ(const __m128& other) const {
#ifdef __SSE4_1__
    __m128 tmp = _mm_dp_ps(data, other, 0x6F);
    return _mm_cvtss_f32(tmp);
#else
    __m128 mul = _mm_mul_ps(data, other);

    __m128 shuf_y = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(1, 1, 1, 1));
    __m128 shuf_z = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 2, 2, 2));

    __m128 sum_yz = _mm_add_ss(shuf_y, shuf_z);
    return _mm_cvtss_f32(sum_yz);
#endif
}

// ================ БАЗОВЫЕ ОПЕРАТОРЫ ================
Vector3d &Vector3d::operator+=(const Vector3d &other) noexcept { return this->operator+=(other.data); }
Vector3d &Vector3d::operator+=(const __m128 &other) noexcept {
    data = _mm_add_ps(data, other);
    return *this;
}

Vector3d &Vector3d::operator-=(const Vector3d &other) noexcept { return this->operator-=(other.data); }
Vector3d &Vector3d::operator-=(const __m128 &other) noexcept {
    data = _mm_sub_ps(data, other);
    return *this;
}

Vector3d &Vector3d::operator*=(const Vector3d &other) noexcept { return this->operator*=(other.data); }
Vector3d &Vector3d::operator*=(const __m128 &other) noexcept {
    data = _mm_mul_ps(data, other);
    return *this;
}

Vector3d &Vector3d::operator/=(const Vector3d &other) noexcept { return this->operator/=(other.data); }
Vector3d &Vector3d::operator/=(const __m128 &other) noexcept {
    data = _mm_div_ps(data, other);
    return *this;
}

float Vector3d::operator^(const Vector3d &other) const noexcept { return this->operator^(other.data); }
float Vector3d::operator^(const __m128 &other) const noexcept { return dot(other); }

Vector3d &Vector3d::operator*=(float scalar) noexcept {
    __m128 scalar_vec = _mm_set1_ps(scalar);
    data = _mm_mul_ps(data, scalar_vec);
    return *this;
}
Vector3d &Vector3d::operator/=(float scalar) noexcept {
    __m128 scalar_vec = _mm_set1_ps(scalar);
    data = _mm_div_ps(data, scalar_vec);
    return *this;
}

Vector3d Vector3d::operator-() const noexcept {
    __m128 sign_mask = _mm_set1_ps(-0.0f);
    return Vector3d(_mm_xor_ps(data, sign_mask));
}

// ================ ГЕОМЕТРИЧЕСКИЕ ФУНКЦИИ ================
float Vector3d::hypot() const noexcept {
    return dot(*this);
}
float Vector3d::length() const noexcept {
    return sqrt(hypot());
}
Vector3d Vector3d::normalize() const noexcept {
    float l = length();
    if (l == 0) {
        return Vector3d(data);
    }
    return (*this) / l;
}

// ================ ОПЕРАТОРЫ СРАВНЕНИЯ (МАСКИ) ================
LogicalMask3d Vector3d::operator==(const Vector3d& other) const noexcept { return this->operator==(other.data); }
LogicalMask3d Vector3d::operator==(float other) const noexcept { return this->operator==(_mm_set1_ps(other)); }
LogicalMask3d Vector3d::operator==(const __m128& other) const noexcept {
    return LogicalMask3d(_mm_cmpeq_ps(data, other));
}

LogicalMask3d Vector3d::operator!=(const Vector3d& other) const noexcept { return this->operator!=(other.data); }
LogicalMask3d Vector3d::operator!=(float other) const noexcept { return this->operator!=(_mm_set1_ps(other)); }
LogicalMask3d Vector3d::operator!=(const __m128& other) const noexcept {
    return LogicalMask3d(_mm_cmpneq_ps(data, other));
}

LogicalMask3d Vector3d::operator>(const Vector3d& other) const noexcept { return this->operator>(other.data); }
LogicalMask3d Vector3d::operator>(float other) const noexcept { return this->operator>(_mm_set1_ps(other)); }
LogicalMask3d Vector3d::operator>(const __m128& other) const noexcept {
    return LogicalMask3d(_mm_cmpgt_ps(data, other));
}

LogicalMask3d Vector3d::operator<(const Vector3d& other) const noexcept { return this->operator<(other.data); }
LogicalMask3d Vector3d::operator<(float other) const noexcept { return this->operator<(_mm_set1_ps(other)); }
LogicalMask3d Vector3d::operator<(const __m128& other) const noexcept {
    return LogicalMask3d(_mm_cmplt_ps(data, other));
}

LogicalMask3d Vector3d::operator>=(const Vector3d& other) const noexcept { return this->operator>=(other.data); }
LogicalMask3d Vector3d::operator>=(float other) const noexcept { return this->operator>=(_mm_set1_ps(other)); }
LogicalMask3d Vector3d::operator>=(const __m128& other) const noexcept {
    return LogicalMask3d(_mm_cmpge_ps(data, other));
}

LogicalMask3d Vector3d::operator<=(const Vector3d& other) const noexcept { return this->operator<=(other.data); }
LogicalMask3d Vector3d::operator<=(float other) const noexcept { return this->operator<=(_mm_set1_ps(other)); }
LogicalMask3d Vector3d::operator<=(const __m128& other) const noexcept {
    return LogicalMask3d(_mm_cmple_ps(data, other));
}

LogicalMask3d Vector3d::toMask() const { return this->operator!=(0.f);}

// ================ БИТОВЫЕ ОПЕРАЦИИ ================
Vector3d &Vector3d::operator&=(const Vector3d &other) noexcept { return this->operator&=(other.data); }
Vector3d &Vector3d::operator&=(const __m128 &other) noexcept {
    data = _mm_and_ps(data, other);
    return *this;
}

Vector3d &Vector3d::operator|=(const Vector3d &other) noexcept { return this->operator|=(other.data); }
Vector3d &Vector3d::operator|=(const __m128 &other) noexcept {
    data = _mm_or_ps(data, other);
    return *this;
}

// ================ УСЛОВНЫЕ ОПЕРАЦИИ ================
float Vector3d::max() const noexcept {
    __m128 d1 = _mm_max_ps(data, _mm_shuffle_ps(data, data, _MM_SHUFFLE(2,2,0,1)));
    __m128 d2 = _mm_max_ss(  d1, _mm_shuffle_ps(  d1,   d1, _MM_SHUFFLE(2,2,2,2)));
    return _mm_cvtss_f32(d2);
}
float Vector3d::min() const noexcept {
    __m128 d1 = _mm_min_ps(data, _mm_shuffle_ps(data, data, _MM_SHUFFLE(2,2,0,1)));
    __m128 d2 = _mm_min_ss(  d1, _mm_shuffle_ps(  d1,   d1, _MM_SHUFFLE(2,2,2,2)));
    return _mm_cvtss_f32(d2);
}

Vector3d Vector3d::abs() const noexcept {
    __m128 sign_mask = _mm_set1_ps(-0.0f);
    return Vector3d(_mm_xor_ps(data, _mm_and_ps(data, sign_mask)));
}
Vector3d Vector3d::sign() const noexcept {
    __m128 sign_mask = _mm_set1_ps(-0.0f);
    return Vector3d(_mm_or_ps(_mm_set1_ps(1.f), _mm_and_ps(data, sign_mask)));
}

Vector3d Vector3d::cross(const Vector3d& other) const noexcept {
    __m128 a_yzx = _mm_shuffle_ps(data, data, _MM_SHUFFLE(3, 0, 2, 1));
    __m128 b_yzx = _mm_shuffle_ps(other.data, other.data, _MM_SHUFFLE(3, 0, 2, 1));

    __m128 a_zxy = _mm_shuffle_ps(data, data, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 b_zxy = _mm_shuffle_ps(other.data, other.data, _MM_SHUFFLE(3, 1, 0, 2));

    __m128 t1 = _mm_mul_ps(a_yzx, b_zxy);
    __m128 t2 = _mm_mul_ps(a_zxy, b_yzx);

    return Vector3d(_mm_sub_ps(t1, t2));
}

DefaultBinOpImpl(Vector3d, +);
DefaultBinOpImpl(Vector3d, -);
DefaultBinOpImpl(Vector3d, *);
DefaultBinOpImpl(Vector3d, /);
DefaultBinOpImpl(Vector3d, &);
DefaultBinOpImpl(Vector3d, |);

LeftBinOpImpl(Vector3d, float, *);
LeftBinOpImpl(Vector3d, float, /);
LeftBinOpImpl(Vector3d, __m128, +);
LeftBinOpImpl(Vector3d, __m128, -);
LeftBinOpImpl(Vector3d, __m128, *);
LeftBinOpImpl(Vector3d, __m128, /);
LeftBinOpImpl(Vector3d, __m128, &);
LeftBinOpImpl(Vector3d, __m128, |);

CommutativeOpImpl(Vector3d, Vector3d, float, *);
CommutativeOpImpl(Vector3d, Vector3d, __m128, +);
CommutativeOpImpl(Vector3d, Vector3d, __m128, *);
CommutativeOpImpl(Vector3d, Vector3d, __m128, &);
CommutativeOpImpl(Vector3d, Vector3d, __m128, |);
CommutativeOpImpl(float, Vector3d, __m128, ^);
