//
// Created by iliya on 4/23/26.
//

#include <xmmintrin.h>
#include "vector3d.h"
#include "funny_defines/classes.h"

#ifndef TRACER_GEOMETRY_LOGICALMASK3D_H
#define TRACER_GEOMETRY_LOGICALMASK3D_H


// Класс маски сравнения (просто обёртка над char)
class LogicalMask3d {
    friend class Vector3d;
private:
    __m128 mask;
    inline explicit LogicalMask3d(__m128 m) noexcept;
public:
    AllowCopy(LogicalMask3d);
    AllowMove(LogicalMask3d);

    inline LogicalMask3d() noexcept;

    // Получение всех трёх булов из маски
    inline bool x() const noexcept;
    inline bool y() const noexcept;
    inline bool z() const noexcept;

    // any <=> в маске хотя бы одна правда
    // all <=> в маске все элементы - правда
    inline bool any() const noexcept;
    inline bool all() const noexcept;

    // Логические операции
    inline LogicalMask3d operator&&(const LogicalMask3d &other) const noexcept;
    inline LogicalMask3d operator||(const LogicalMask3d &other) const noexcept;
    inline LogicalMask3d operator^(const LogicalMask3d &other) const noexcept;
    inline LogicalMask3d operator!() const noexcept;

    // Применение маски к вектору
    inline Vector3d operator*(const Vector3d &other) const noexcept;
    // Условие на вектор по маске
    inline Vector3d combine(const Vector3d &true_v, const Vector3d &false_v) const noexcept;

    // Немного конвертаций
    inline char toChar() const noexcept;
    inline Vector3d toVector() const noexcept;
};

#endif // TRACER_GEOMETRY_LOGICALMASK3D_H
