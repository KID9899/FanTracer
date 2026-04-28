//
// Created by iliya on 4/19/26.
//

#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_INTERFACES_MATERIAL_H
#define TRACER_INTERFACES_MATERIAL_H

// Интерфейс для материала
// TODO - добавить текстуры
class IMaterial {
public:
    virtual ~IMaterial() = default;
    // Производит взаимодействие луча с телом
    // Ввод:
    //   in - луч, пересекшийся с телом
    //   hit - информация о пересечении
    // Вывод:
    //   absorption_attenuation - прямое поглощение (поглощение луча, отражённого в камеру)
    //   distortion_attenuation - поглощение искажённого луча (затцхание при отражении, просвете и так далее)
    //   scattered - луч, получившийся после "столкновения" луча in с материалом
    virtual bool scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const = 0;
    // Выводит неизменяемую составляющую цвета (свечение) в точке hit-а
    virtual const Vector3d emitted(const HitRecord& hit) const {
        return Vector3d(0, 0, 0);
    }
};

#endif // TRACER_INTERFACES_MATERIAL_H
