//
// Created by iliya on 4/19/26.
//

#include "tracer/geometry.h"

#ifndef TRACER_INTERFACES_MATERIAL_H
#define TRACER_INTERFACES_MATERIAL_H

class IMaterial {
public:
    virtual ~IMaterial() = default;

    virtual bool scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const = 0;

    virtual const Vector3d emitted(const HitRecord& hit, const Vector3d& point) const {
        return Vector3d(0, 0, 0);
    }
};

#endif // TRACER_INTERFACES_MATERIAL_H
