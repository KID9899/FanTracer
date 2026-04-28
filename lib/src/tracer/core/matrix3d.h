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
    explicit Matrix3d(__m128 col0, __m128 col1, __m128 col2);
public:
    AllowCopyDecl(Matrix3d);
    AllowMoveDecl(Matrix3d);
    DestructorDecl(Matrix3d);

    // Дефолтный конструктор нуль-матрицы
    Matrix3d();
    // Сборка матрицы из столбцов и строк
    static Matrix3d concatCols(Float3 col0, Float3 col1, Float3 col2);
    static Matrix3d concatRows(Float3 row0, Float3 row1, Float3 row2);
    // Математические матрицы
    static Matrix3d eye();
    static Matrix3d diag(float x);
    static Matrix3d fill(float x);
    // Максимально "сырой" конструктор
    // Его использование извне нежелательно, но возможно
    // для различных вычислительных функций
    static Matrix3d unsafeCreateFromXMM(__m128 col0, __m128 col1, __m128 col2);

    // Простые операторы
    Matrix3d& operator+=(const Matrix3d& other);
    Matrix3d& operator-=(const Matrix3d& other);
    Matrix3d& operator*=(const Matrix3d& other);
    Matrix3d& operator/=(const Matrix3d& other);

    // Домножение на скаляр
    Matrix3d& operator*=(float other);
    Matrix3d& operator/=(float other);

    // Домножение на вектор
    Vector3d apply(const Vector3d& v) const;
};

Vector3d operator^(const Matrix3d& m, const Vector3d& v) noexcept;

DefaultBinOpDecl(Matrix3d, +);
DefaultBinOpDecl(Matrix3d, -);
DefaultBinOpDecl(Matrix3d, *);
DefaultBinOpDecl(Matrix3d, /);

LeftBinOpDecl(Matrix3d, float, *);
LeftBinOpDecl(Matrix3d, float, /);

CommutativeOpDecl(Matrix3d, Matrix3d, float, *);

// Короткие названия для удобства
namespace tracer_short_names {
    typedef Matrix3d M3;
}

#endif // TRACER_GEOMETRY_MATRIX3D_H
