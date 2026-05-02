//
// Created by iliya on 4/19/26.
//

#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_INTERFACES_SHAPE_H
#define TRACER_INTERFACES_SHAPE_H

// Интерфейс для тела
class IShape {
public:
    virtual ~IShape() = default;
    // Функция, пишущая в hit информацию о пересечении луча ray с телом
    // на промежутке от t_min до t_max
    // если пересечения не было, возвращает false
    virtual bool intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const noexcept = 0;
    // Возвращает AABB тела для оптимизации рендера
    // TODO - добавить учёт AABB для оптимизации
    virtual AABB getBoundingBox() const noexcept = 0;
};

#endif // TRACER_INTERFACES_SHAPE_H
