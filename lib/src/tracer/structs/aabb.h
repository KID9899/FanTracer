//
// Created by iliya on 4/19/26.
//

#include "tracer/core.h"

#ifndef TRACER_GEOMETRY_AABB_H
#define TRACER_GEOMETRY_AABB_H

// Простая структура для хранения AABB
// TODO - улучшить, добавить поддержку во время рендеринга
struct AABB {
    Vector3d min;
    Vector3d max;
};

#endif // TRACER_GEOMETRY_AABB_H
