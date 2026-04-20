//
// Created by iliya on 4/19/26.
//

#include "tracer/geometry.h"

#ifndef TRACER_INTERFACES_LIGHT_H
#define TRACER_INTERFACES_LIGHT_H

// Интерфейс для объекта, испускающего свет
// TODO - сделать светящиеся текстуры... как-нибудь
class ILight {
public:
    virtual ~ILight() = default;

    // Возвращает RGB-вектор интенсивности освещения в точке пересечения (из hit)
    virtual const Vector3d illuminate(const HitRecord& hit, Vector3d& light_dir, float& distance) const = 0;
    // Выбрать случайную точку источника
    virtual const Vector3d samplePoint() const = 0;
};

#endif // TRACER_INTERFACES_LIGHT_H
