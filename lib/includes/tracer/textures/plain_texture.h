//
// Created by iliya on 5/3/26.
//

#ifndef TRACER_TEXTURES_PLAIN_TEXTURE_H
#define TRACER_TEXTURES_PLAIN_TEXTURE_H

#include "tracer/interfaces.h"
#include "tracer/core.h"

class PlainTexture : public ITexture {
    Vector3d color;
public:
    inline PlainTexture(const Vector3d& c) noexcept : color(c) {}
    void get_attenuation(float, float, Vector3d& absorption, Vector3d& distortion) const noexcept override {
        absorption = color;
        distortion = color;
    }
};

#endif
