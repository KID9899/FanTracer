//
// Created by iliya on 4/19/26.
//

#include "lambertian.h"
#include "tracer/geometry.h"

Lambertian::Lambertian(const Vector3d &color): color(color) {}

bool Lambertian::scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const {
    // Матовое размытие
    scattered = {hit.point, hit.normal + randomInUnitSphere()};
    absorption_attenuation = color;
    // TODO - убедиться в правильности
    distortion_attenuation = color;
    return true;
}
