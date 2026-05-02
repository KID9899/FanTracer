//
// Created by iliya on 4/19/26.
//

#include "tracer/core.h"
#include "ray.h"

#ifndef TRACER_GEOMETRY_AABB_H
#define TRACER_GEOMETRY_AABB_H

// Простая структура для хранения AABB
// TODO - улучшить, добавить поддержку во время рендеринга
struct AABB {
    Vector3d min;
    Vector3d max;

    inline bool hit(const Ray& ray, float t_min, float t_max) const noexcept {
        Vector3d invDir = Vector3d(1.0f) / ray.direction;
        Vector3d t0 = (min - ray.origin) * invDir;
        Vector3d t1 = (max - ray.origin) * invDir;

        LogicalMask3d mask = invDir < 0.0f;
        Vector3d tMin = mask.combine(t1, t0);
        Vector3d tMax = mask.combine(t0, t1);

        float tEnter = tMin.max();
        float tExit  = tMax.min();

        return tEnter <= tExit && tExit >= t_min && tEnter <= t_max;
    }
};

#endif // TRACER_GEOMETRY_AABB_H
