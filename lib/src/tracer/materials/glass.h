//
// Created by iliya on 4/19/26.
//

#include "tracer/interfaces.h"
#include "tracer/geometry.h"

#ifndef TRACER_MATERIALS_GLASS_H
#define TRACER_MATERIALS_GLASS_H

class Glass : public IMaterial {
    Vector3d albedo;
    float refraction_index;
    float reflection_coeff;
    float tint_coeff;
public:
    Glass(const Vector3d& color, float ri, float refl_coeff, float tint);

    bool scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const override;
};

#endif // TRACER_MATERIALS_GLASS_H
