//
// Created by iliya on 4/23/26.
//

#include "sky_light.h"

SkyLight::SkyLight(const Vector3d &intensity): intensity(intensity) {}

const Vector3d SkyLight::illuminate(const HitRecord &hit, Vector3d &light_dir, float &distance) const {
    light_dir = hit.normal;
    distance = 0;
    return intensity;
}

const Vector3d SkyLight::samplePoint() const { return {1e18f, 1e18f, 1e18f}; }
