//
// Created by iliya on 4/23/26.
//

#include <xmmintrin.h>
#include "vector3d.h"
#include "logicalmask3d.h"

#ifdef __SSE4_1__
    #include <smmintrin.h>
#endif

#pragma once

inline LogicalMask3d::LogicalMask3d(__m128 m) noexcept: mask(m) {}
inline LogicalMask3d::LogicalMask3d() noexcept: mask(_mm_set1_ps(0.f)) {}

inline bool LogicalMask3d::x() const noexcept { return (_mm_movemask_ps(mask) & 1) != 0; }
inline bool LogicalMask3d::y() const noexcept { return (_mm_movemask_ps(mask) & 2) != 0; }
inline bool LogicalMask3d::z() const noexcept { return (_mm_movemask_ps(mask) & 4) != 0; }

inline bool LogicalMask3d::any() const noexcept { return (_mm_movemask_ps(mask) & 0x7) != 0; }
inline bool LogicalMask3d::all() const noexcept { return (_mm_movemask_ps(mask) & 0x7) == 0x7; }


inline LogicalMask3d LogicalMask3d::operator&&(const LogicalMask3d &other) const noexcept {
    return LogicalMask3d(_mm_and_ps(mask, other.mask));
}
inline LogicalMask3d LogicalMask3d::operator||(const LogicalMask3d &other) const noexcept {
    return LogicalMask3d(_mm_or_ps(mask, other.mask));
}
inline LogicalMask3d LogicalMask3d::operator^(const LogicalMask3d &other) const noexcept {
    return LogicalMask3d(_mm_xor_ps(mask, other.mask));
}
inline LogicalMask3d LogicalMask3d::operator!() const noexcept {
    __m128i mi = _mm_castps_si128(mask);
    __m128i tmp = _mm_xor_si128(mi, _mm_set1_epi32(-1));
    return LogicalMask3d(_mm_castsi128_ps(tmp));
}


inline char LogicalMask3d::toChar() const noexcept { return _mm_movemask_ps(mask) & 0x07; }
inline Vector3d LogicalMask3d::toVector() const noexcept {
    char mv = toChar();
    return Vector3d(static_cast<float>((mv & 1) != 0), static_cast<float>((mv & 2) != 0), static_cast<float>((mv & 4) != 0));
}

inline Vector3d LogicalMask3d::operator*(const Vector3d &other) const noexcept {
    return other & mask;
}

inline Vector3d LogicalMask3d::combine(const Vector3d &true_v, const Vector3d &false_v) const noexcept {
#ifdef __SSE4_1__
    return Vector3d::unsafeCreateFromXMM(_mm_blendv_ps(false_v, true_v, mask));
#else
    __m128i mi = _mm_castps_si128(mask);
    __m128i tmp = _mm_xor_si128(mi, _mm_set1_epi32(-1));
    __m128 inv = _mm_castsi128_ps(tmp);
    return (true_v & mask) | (false_v & inv);
#endif
}
