//
// Created by iliya on 4/19/26.
//

#include "tracer/geometry.h"

#ifndef TRACER_INTERFACES_SHAPE_H
#define TRACER_INTERFACES_SHAPE_H

class IShape {
public:
    virtual ~IShape() = default;

    virtual bool intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const = 0;

    virtual AABB getBoundingBox() const = 0;
};

#endif // TRACER_INTERFACES_SHAPE_H
