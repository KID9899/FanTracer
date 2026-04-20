//
// Created by iliya on 4/19/26.
//

#include "tracer/interfaces.h"
#include "tracer/geometry.h"

#ifndef TRACER_MATERIALS_LAMBERTIAN_H
#define TRACER_MATERIALS_LAMBERTIAN_H

class Lambertian : public IMaterial {
    const Vector3d albedo;
public:
    Lambertian(const Vector3d& color);

    bool scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const override;
};

#endif // TRACER_MATERIALS_LAMBERTIAN_H
