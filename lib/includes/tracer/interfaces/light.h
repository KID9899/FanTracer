//
// Created by iliya on 4/19/26.
//

#include "tracer/geometry.h"

#ifndef TRACER_INTERFACES_LIGHT_H
#define TRACER_INTERFACES_LIGHT_H

class ILight {
public:
    virtual ~ILight() = default;

    virtual const Vector3d illuminate(const HitRecord& hit, Vector3d& light_dir, float& distance) const = 0;

    virtual const Vector3d samplePoint() const = 0;
};

#endif // TRACER_INTERFACES_LIGHT_H
