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
    explicit LogicalMask3d(__m128 m) noexcept : mask(m) {}
public:
    AllowCopyDecl(LogicalMask3d);
    AllowMoveDecl(LogicalMask3d);
    DestructorDecl(LogicalMask3d);

    LogicalMask3d() noexcept;

    // Получение всех трёх булов из маски
    bool x() const noexcept;
    bool y() const noexcept;
    bool z() const noexcept;

    // any <=> в маске хотя бы одна правда
    // all <=> в маске все элементы - правда
    bool any() const noexcept;
    bool all() const noexcept;

    // Логические операции
    LogicalMask3d operator&&(const LogicalMask3d& other) const noexcept;
    LogicalMask3d operator||(const LogicalMask3d& other) const noexcept;
    LogicalMask3d operator^(const LogicalMask3d& other) const noexcept;
    LogicalMask3d operator!() const noexcept;

    // Применение маски к вектору
    Vector3d operator*(const Vector3d& other) const noexcept;
    // Условие на вектор по маске
    Vector3d combine(const Vector3d& true_v, const Vector3d& false_v) const noexcept;

    // Немного конвертаций
    char toChar() const;
    Vector3d toVector() const;
};

CommutativeOpDecl(Vector3d, LogicalMask3d, Vector3d, *);
#endif // TRACER_GEOMETRY_LOGICALMASK3D_H
