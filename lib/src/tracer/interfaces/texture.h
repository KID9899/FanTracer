//
// Created by iliya on 5/3/26.
//

#ifndef TRACER_INTERFACES_TEXTURE_H
#define TRACER_INTERFACES_TEXTURE_H

#include "tracer/core.h"

class ITexture {
public:
    virtual ~ITexture() = default;
    virtual void get_attenuation(float u, float v, Vector3d& absorption, Vector3d& distortion) const noexcept = 0;
    virtual Vector3d emitted(float u, float v) const noexcept { return Vector3d(0,0,0); }
};

#endif // TRACER_INTERFACES_TEXTURE_H
