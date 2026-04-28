//
// Created by iliya on 4/18/26.
//

#include <xmmintrin.h>
#include "float3.h"
#include "funny_defines/classes.h"

#ifndef TRACER_GEOMETRY_VECTOR3D_H
#define TRACER_GEOMETRY_VECTOR3D_H

class LogicalMask3d;

// Класс для обработки точек и векторов в 3D
class Vector3d {
private:
    __m128 data; // x, y, z, w
    explicit Vector3d(__m128 data) noexcept;
public:
    // Для обеспечения нормального возвращения из функций
    // И присваивания
    AllowCopyDecl(Vector3d);
    AllowMoveDecl(Vector3d);
    DestructorDecl(Vector3d);

    // Стандартный конструктор 3D-вектора
    Vector3d(float x, float y, float z) noexcept;
    // Конструктор для float
    explicit Vector3d(float fill) noexcept;
    // Пустой конструктор для нуль-вектора
    Vector3d() noexcept;
    // Конструктор для неявного каста (по структуре других быть не должно)
    Vector3d(const Float3& f3);
    // Максимально "сырой" конструктор
    // Его использование извне нежелательно, но возможно
    // для различных вычислительных функций
    static Vector3d unsafeCreateFromXMM(__m128 data) noexcept;

    // Методы для получения конкретных значений (не рекомендуется использовать)
    float getX() const;
    float getY() const;
    float getZ() const;
    // Метод для получения m128
    __m128 getData() const;

    // Замена одного компонента (для текущего вектора)
    Vector3d replaceX(float newX) const noexcept;
    Vector3d replaceY(float newY) const noexcept;
    Vector3d replaceZ(float newZ) const noexcept;

    // Скалярное произведения
    float dot(const Vector3d& other) const;
    float dot(const __m128& other) const;
    // Частичные скалярные произведения
    float dotXY(const Vector3d& other) const;
    float dotXY(const __m128& other) const;
    float dotXZ(const Vector3d& other) const;
    float dotXZ(const __m128& other) const;
    float dotYZ(const Vector3d& other) const;
    float dotYZ(const __m128& other) const;

    // Немного для удобной математики
    // * и / - поэлементное, ^ - скалярное произведение
    Vector3d& operator+=(const Vector3d& other) noexcept;
    Vector3d& operator+=(const __m128& other) noexcept;
    Vector3d& operator-=(const Vector3d& other) noexcept;
    Vector3d& operator-=(const __m128& other) noexcept;
    Vector3d& operator*=(const Vector3d& other) noexcept;
    Vector3d& operator*=(const __m128& other) noexcept;
    Vector3d& operator/=(const Vector3d& other) noexcept;
    Vector3d& operator/=(const __m128& other) noexcept;

    Vector3d& operator*=(float scalar) noexcept;
    Vector3d& operator/=(float scalar) noexcept;

    float operator^(const Vector3d& other) const noexcept;
    float operator^(const __m128& other) const noexcept;

    Vector3d operator-() const noexcept;

    // Побитовые операции
    Vector3d& operator&=(const Vector3d& other) noexcept;
    Vector3d& operator&=(const __m128& other) noexcept;
    Vector3d& operator|=(const Vector3d& other) noexcept;
    Vector3d& operator|=(const __m128& other) noexcept;

    // Логические операции
    // Важно! Для безопасности в использовании они все будут
    // исключительно ЛЕВЫМИ (то есть если other - не Vector3d, разрешены
    // только операции вида Vector3d >= other, а other <= Vector3d запрещены)
    LogicalMask3d operator==(const Vector3d& other) const noexcept;
    LogicalMask3d operator!=(const Vector3d& other) const noexcept;
    LogicalMask3d operator>(const Vector3d& other) const noexcept;
    LogicalMask3d operator<(const Vector3d& other) const noexcept;
    LogicalMask3d operator>=(const Vector3d& other) const noexcept;
    LogicalMask3d operator<=(const Vector3d& other) const noexcept;

    LogicalMask3d operator==(const __m128& other) const noexcept;
    LogicalMask3d operator!=(const __m128& other) const noexcept;
    LogicalMask3d operator>(const __m128& other) const noexcept;
    LogicalMask3d operator<(const __m128& other) const noexcept;
    LogicalMask3d operator>=(const __m128& other) const noexcept;
    LogicalMask3d operator<=(const __m128& other) const noexcept;

    // В случае с float - проверка ведётся по всем элементам
    // То есть self op Vector3d(other)
    LogicalMask3d operator==(float other) const noexcept;
    LogicalMask3d operator!=(float other) const noexcept;
    LogicalMask3d operator>(float other) const noexcept;
    LogicalMask3d operator<(float other) const noexcept;
    LogicalMask3d operator>=(float other) const noexcept;
    LogicalMask3d operator<=(float other) const noexcept;

    // Просто v != 0
    LogicalMask3d toMask() const;

    // hypot - это просто x*x + y*y + z*z
    // А length - длинна вектора
    float hypot() const noexcept;
    float length() const noexcept;

    // Максимальное и минимальное число
    float max() const noexcept;
    float min() const noexcept;

    // Модуль каждого значения
    Vector3d abs() const noexcept;
    // Знак (+-1 в любом случае, если 0 берётся знак нуля)
    Vector3d sign() const noexcept;
    // Нормализация вектора
    Vector3d normalize() const noexcept;

    // Векторное произведение
    Vector3d cross(const Vector3d& other) const noexcept;
};

DefaultBinOpDecl(Vector3d, +);
DefaultBinOpDecl(Vector3d, -);
DefaultBinOpDecl(Vector3d, *);
DefaultBinOpDecl(Vector3d, /);
DefaultBinOpDecl(Vector3d, &);
DefaultBinOpDecl(Vector3d, |);

LeftBinOpDecl(Vector3d, float, *);
LeftBinOpDecl(Vector3d, float, /);
LeftBinOpDecl(Vector3d, __m128, +);
LeftBinOpDecl(Vector3d, __m128, -);
LeftBinOpDecl(Vector3d, __m128, *);
LeftBinOpDecl(Vector3d, __m128, /);
LeftBinOpDecl(Vector3d, __m128, &);
LeftBinOpDecl(Vector3d, __m128, |);

CommutativeOpDecl(Vector3d, Vector3d, float, *);
CommutativeOpDecl(Vector3d, Vector3d, __m128, +);
CommutativeOpDecl(Vector3d, Vector3d, __m128, *);
CommutativeOpDecl(Vector3d, Vector3d, __m128, &);
CommutativeOpDecl(Vector3d, Vector3d, __m128, |);
CommutativeOpDecl(float, Vector3d, __m128, ^);

// Короткие названия для удобства
namespace tracer_short_names {
    typedef Vector3d V3;
}

#endif // TRACER_GEOMETRY_VECTOR3D_H
