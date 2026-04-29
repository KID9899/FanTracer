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
    inline explicit Vector3d(__m128 data) noexcept;
public:
    // Для обеспечения нормального возвращения из функций
    // И присваивания
    AllowCopy(Vector3d);
    AllowMove(Vector3d);

    // Стандартный конструктор 3D-вектора
    inline Vector3d(float x, float y, float z) noexcept;
    // Конструктор для float
    inline explicit Vector3d(float fill) noexcept;
    // Пустой конструктор для нуль-вектора
    inline Vector3d() noexcept;
    // Конструктор для неявного каста (по структуре других быть не должно)
    inline Vector3d(const Float3 &f3) noexcept;
    // Максимально "сырой" конструктор
    // Его использование извне нежелательно, но возможно
    // для различных вычислительных функций
    inline static Vector3d unsafeCreateFromXMM(__m128 data) noexcept;

    // Методы для получения конкретных значений (не рекомендуется использовать)
    inline float getX() const noexcept;
    inline float getY() const noexcept;
    inline float getZ() const noexcept;
    // Метод для получения m128
    inline __m128 getData() const noexcept;

    // Замена одного компонента (для текущего вектора)
    inline Vector3d replaceX(float newX) const noexcept;
    inline Vector3d replaceY(float newY) const noexcept;
    inline Vector3d replaceZ(float newZ) const noexcept;

    // Скалярное произведения
    inline float dot(const Vector3d &other) const noexcept;
    inline float dot(__m128 other) const noexcept;
    // Частичные скалярные произведения
    inline float dotXY(const Vector3d &other) const noexcept;
    inline float dotXY(__m128 other) const noexcept;
    inline float dotXZ(const Vector3d &other) const noexcept;
    inline float dotXZ(__m128 other) const noexcept;
    inline float dotYZ(const Vector3d &other) const noexcept;
    inline float dotYZ(__m128 other) const noexcept;

    // Немного для удобной математики
    // * и / - поэлементное, ^ - скалярное произведение
    inline Vector3d &operator+=(const Vector3d &other) noexcept;
    inline Vector3d &operator+=(__m128 other) noexcept;
    inline Vector3d &operator-=(const Vector3d &other) noexcept;
    inline Vector3d &operator-=(__m128 other) noexcept;
    inline Vector3d &operator*=(const Vector3d &other) noexcept;
    inline Vector3d &operator*=(__m128 other) noexcept;
    inline Vector3d &operator/=(const Vector3d &other) noexcept;
    inline Vector3d &operator/=(__m128 other) noexcept;

    inline Vector3d &operator*=(float scalar) noexcept;
    inline Vector3d &operator/=(float scalar) noexcept;

    inline float operator^(const Vector3d &other) const noexcept;
    inline float operator^(__m128 other) const noexcept;

    inline Vector3d operator-() const noexcept;

    // Побитовые операции
    inline Vector3d &operator&=(const Vector3d &other) noexcept;
    inline Vector3d &operator&=(__m128 other) noexcept;
    inline Vector3d &operator|=(const Vector3d &other) noexcept;
    inline Vector3d &operator|=(__m128 other) noexcept;

    // Логические операции
    // Важно! Для безопасности в использовании они все будут
    // исключительно ЛЕВЫМИ (то есть если other - не Vector3d, разрешены
    // только операции вида Vector3d >= other, а other <= Vector3d запрещены)
    inline LogicalMask3d operator==(const Vector3d &other) const noexcept;
    inline LogicalMask3d operator!=(const Vector3d &other) const noexcept;
    inline LogicalMask3d operator>(const Vector3d &other) const noexcept;
    inline LogicalMask3d operator<(const Vector3d &other) const noexcept;
    inline LogicalMask3d operator>=(const Vector3d &other) const noexcept;
    inline LogicalMask3d operator<=(const Vector3d &other) const noexcept;

    inline LogicalMask3d operator==(__m128 other) const noexcept;
    inline LogicalMask3d operator!=(__m128 other) const noexcept;
    inline LogicalMask3d operator>(__m128 other) const noexcept;
    inline LogicalMask3d operator<(__m128 other) const noexcept;
    inline LogicalMask3d operator>=(__m128 other) const noexcept;
    inline LogicalMask3d operator<=(__m128 other) const noexcept;

    // В случае с float - проверка ведётся по всем элементам
    // То есть self op Vector3d(other)
    inline LogicalMask3d operator==(float other) const noexcept;
    inline LogicalMask3d operator!=(float other) const noexcept;
    inline LogicalMask3d operator>(float other) const noexcept;
    inline LogicalMask3d operator<(float other) const noexcept;
    inline LogicalMask3d operator>=(float other) const noexcept;
    inline LogicalMask3d operator<=(float other) const noexcept;

    // Просто v != 0
    inline LogicalMask3d toMask() const noexcept;

    // hypot - это просто x*x + y*y + z*z
    // А length - длинна вектора
    inline float hypot() const noexcept;
    inline float length() const noexcept;

    // Максимальное и минимальное число
    inline float max() const noexcept;
    inline float min() const noexcept;

    // Модуль каждого значения
    inline Vector3d abs() const noexcept;
    // Знак (+-1 в любом случае, если 0 берётся знак нуля)
    inline Vector3d sign() const noexcept;
    // Нормализация вектора
    inline Vector3d normalize() const noexcept;

    // Векторное произведение
    Vector3d cross(const Vector3d &other) const noexcept;
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

CommutativeOpDecl(Vector3d, const Vector3d&, float, *);
CommutativeOpDecl(Vector3d, const Vector3d&, __m128, +);
CommutativeOpDecl(Vector3d, const Vector3d&, __m128, *);
CommutativeOpDecl(Vector3d, const Vector3d&, __m128, &);
CommutativeOpDecl(Vector3d, const Vector3d&, __m128, |);
CommutativeOpDecl(float, const Vector3d&, __m128, ^);

// Короткие названия для удобства
namespace tracer_short_names {
    typedef Vector3d V3;
}

#endif // TRACER_GEOMETRY_VECTOR3D_H
