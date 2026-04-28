//
// Created by iliya on 4/19/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_MATERIALS_LAMBERTIAN_H
#define TRACER_MATERIALS_LAMBERTIAN_H

// Классический матовый материал
class Lambertian : public IMaterial {
    // Цвет материала
    const Vector3d color;
public:
    Lambertian(const Vector3d& color);

    bool scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const override;
};

#endif // TRACER_MATERIALS_LAMBERTIAN_H
