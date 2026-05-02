//
// Created by iliya on 4/23/26.
//

#include <xmmintrin.h>
#include "vector3d.h"
#include "funny_defines/classes.h"

#ifndef TRACER_GEOMETRY_MATRIX3D_H
#define TRACER_GEOMETRY_MATRIX3D_H

class Matrix3d {
private:
    // colX = _mm_set_ps(0.f, a2X, a1X, a0X)
    // ---------------
    // a00 | a01 | a02
    // a10 | a11 | a12
    // a20 | a21 | a22
    // ---------------
    __m128 col0, col1, col2;
    inline explicit Matrix3d(__m128 col0, __m128 col1, __m128 col2) noexcept;
public:
    AllowCopy(Matrix3d);
    AllowMove(Matrix3d);

    // Дефолтный конструктор нуль-матрицы
    inline Matrix3d() noexcept;
    // Сборка матрицы из столбцов и строк
    inline static Matrix3d concatCols(const Float3 &col0, const Float3 &col1, const Float3 &col2) noexcept;
    inline static Matrix3d concatRows(const Float3 &row0, const Float3 &row1, const Float3 &row2) noexcept;
    // Математические матрицы
    inline static Matrix3d eye() noexcept;
    inline static Matrix3d diag(float x) noexcept;
    inline static Matrix3d fill(float x) noexcept;
    // Максимально "сырой" конструктор
    // Его использование извне нежелательно, но возможно
    // для различных вычислительных функций
    inline static Matrix3d unsafeCreateFromXMM(__m128 col0, __m128 col1, __m128 col2) noexcept;

    // Простые операторы
    inline Matrix3d &operator+=(const Matrix3d &other) noexcept;
    inline Matrix3d &operator-=(const Matrix3d &other) noexcept;
    inline Matrix3d &operator*=(const Matrix3d &other) noexcept;
    inline Matrix3d &operator/=(const Matrix3d &other) noexcept;

    // Домножение на скаляр
    inline Matrix3d &operator*=(float other) noexcept;
    inline Matrix3d &operator/=(float other) noexcept;

    // Домножение на вектор
    inline Vector3d apply(const Vector3d &v) const noexcept;
};

inline Vector3d operator^(const Matrix3d &m, const Vector3d &v) noexcept;

inline DefaultBinOpDecl(Matrix3d, +);
inline DefaultBinOpDecl(Matrix3d, -);
inline DefaultBinOpDecl(Matrix3d, *);
inline DefaultBinOpDecl(Matrix3d, /);

LeftBinOpDecl(Matrix3d, float, *);
LeftBinOpDecl(Matrix3d, float, /);

CommutativeOpDecl(Matrix3d, const Matrix3d&, float, *);

// Короткие названия для удобства
namespace tracer_short_names {
    typedef Matrix3d M3;
}

#endif // TRACER_GEOMETRY_MATRIX3D_H
