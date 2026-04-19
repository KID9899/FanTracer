//
// Created by iliya on 4/19/26.
//

#include "tracer/interfaces.h"
#include "tracer/geometry.h"

#ifndef TRACER_MATERIALS_METAL_H
#define TRACER_MATERIALS_METAL_H

class Metal : public IMaterial {
    Vector3d albedo;
    float fuzz;
public:
    Metal(const Vector3d& albedo, float fuzz);

    bool scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const override;
};


#endif // TRACER_MATERIALS_METAL_H
