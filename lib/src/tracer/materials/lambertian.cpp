//
// Created by iliya on 4/19/26.
//

#include "lambertian.h"

Lambertian::Lambertian(const Vector3d &color): albedo(color) {}

bool Lambertian::scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const {
    scattered = {hit.point, hit.normal + randomInUnitSphere()};
    absorption_attenuation = albedo;
    distortion_attenuation = albedo;
    return true;
}
