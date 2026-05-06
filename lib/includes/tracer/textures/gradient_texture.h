//
// Created by iliya on 5/3/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"

#ifndef TRACER_TEXTURES_GRADIENT_TEXTURE_H
#define TRACER_TEXTURES_GRADIENT_TEXTURE_H

class GradientTexture : public ITexture {
    Vector3d color0, color1;
public:
    inline GradientTexture(const Vector3d& c0, const Vector3d& c1) noexcept : color0(c0), color1(c1) {}
    void get_attenuation(float u, float v, Vector3d& absorption, Vector3d& distortion) const noexcept override {
        float t = std::min(std::max(u, 0.f), 1.f);
        Vector3d c = color0 * (1.f - t) + color1 * t;
        absorption = c;
        distortion = c;
    }
};

#endif
