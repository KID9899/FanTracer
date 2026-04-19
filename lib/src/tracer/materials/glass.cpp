//
// Created by iliya on 4/19/26.
//

#include "glass.h"
#include <cmath>

Glass::Glass(const Vector3d &color, float ri, float refl_coeff, float tint)
        : albedo(color), refraction_index(ri), reflection_coeff(refl_coeff), tint_coeff(tint) {}

bool Glass::scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const {
    Vector3d unit_direction = in.direction.normalize();
    Vector3d reflected = unit_direction.reflect(hit.normal);

    Vector3d white(1.0f, 1.0f, 1.0f);
    absorption_attenuation = Vector3d(0.0f, 0.0f, 0.0f);
    distortion_attenuation = white * (1.0f - tint_coeff) + albedo * tint_coeff;

    Vector3d outward_normal;
    float ni_over_nt;
    if (unit_direction * hit.normal > 0.0f) {
        outward_normal = -hit.normal;
        ni_over_nt = refraction_index;
    } else {
        outward_normal = hit.normal;
        ni_over_nt = 1.0f / refraction_index;
    }

    float dt = unit_direction * outward_normal;
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);

    if (discriminant <= 0.0f) {
        scattered = {hit.point, reflected};
        return true;
    }

    Vector3d r = randomInUnitSphere();
    float rand_val = (r.getX() + 1.0f) / 2.0f;

    if (rand_val < reflection_coeff) {
        scattered = {hit.point, reflected};
    } else {
        Vector3d refracted = ni_over_nt * (unit_direction - outward_normal * dt) - outward_normal * std::sqrt(discriminant);
        scattered = {hit.point, refracted};
    }

    return true;
}
