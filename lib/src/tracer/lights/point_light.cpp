//
// Created by iliya on 4/19/26.
//

#include "point_light.h"

PointLight::PointLight(const Vector3d &position, const Vector3d &intensity): position(position), intensity(intensity) {}

const Vector3d PointLight::illuminate(const HitRecord &hit, Vector3d &light_dir, float &distance) const {
    light_dir = position - hit.point;
    distance = light_dir.length();
    light_dir /= distance;
    return intensity / (distance * distance);
}

const Vector3d PointLight::samplePoint() const { return position; }
