//
// Created by iliya on 4/19/26.
//

#include "vector3d.h"

#ifndef TRACER_GEOMETRY_HIT_RECORD_H
#define TRACER_GEOMETRY_HIT_RECORD_H

class IMaterial;

// Структура, содержащая информацию об пересечении луча и тела
// TODO - добавить поддержку текстур
// TODO - добавить механику пакетов для SIMD
struct HitRecord {
    // Расстояние от начала луча до точки пересечения
    float t;
    // Точка пересечения
    Vector3d point;
    // Нормаль к поверхности в указанной точке
    Vector3d normal;
    // Ссылка на материал тела
    const IMaterial* material;
    // Вошёл ли луч в объект (true) или вышел (false)
    bool frontFace;
};

#endif // TRACER_GEOMETRY_HIT_RECORD_H
