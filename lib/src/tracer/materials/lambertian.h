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
public:
    inline Lambertian(const ITexture* tex) noexcept : IMaterial(tex) {}
    bool scatter_ray(const Ray& in, const HitRecord& hit, Ray& scattered) const noexcept override;
};

#endif // TRACER_MATERIALS_LAMBERTIAN_H
