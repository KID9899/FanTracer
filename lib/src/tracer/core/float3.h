//
// Created by iliya on 4/23/26.
//

#ifndef TRACER_GEOMETRY_FLOAT3_H
#define TRACER_GEOMETRY_FLOAT3_H

// Структура для хранения трёх неависимых float
// Создана для того, чтоб SIMD-вектора и просто три независимых float
// Можно было создать одинаково через Float3{x, y, z};
// Так как у SIMD-вектора есть не-explicit конструктор от const &Float3d;
struct Float3 {
    float x = 0.f, y = 0.f, z = 0.f;
};

// Короткие названия для удобства
namespace tracer_short_names {
    typedef Float3 F3;
}

#endif // TRACER_GEOMETRY_FLOAT3_H
