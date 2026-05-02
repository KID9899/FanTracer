//
// Created by iliya on 4/19/26.
//

#include <cmath>
#include "glass.h"
#include "tracer/geometry.h"

Glass::Glass(const Vector3d &color, float ri, float refl, float tint) noexcept
        : color(color), refraction_index(ri), reflection_coeff(refl), tint_coeff(tint) {}

bool Glass::scatter(const Ray &in, const HitRecord &hit, Vector3d &absorption_attenuation, Vector3d &distortion_attenuation, Ray &scattered) const noexcept {
    Vector3d unit_direction = in.direction.normalize();
    Vector3d reflected = reflect(unit_direction, hit.normal);

    // TODO - переделать формулы на чистовой вариант
    Vector3d white(1.0f, 1.0f, 1.0f);
    absorption_attenuation = Vector3d(0.0f, 0.0f, 0.0f);
    distortion_attenuation = white * (1.0f - tint_coeff) + color * tint_coeff;

    // Параметры для преломления луча и поиск подходящей нормали
    // TODO - перейти на параметры hit-а
    Vector3d outward_normal;
    float ni_over_nt;
    if ((unit_direction ^ hit.normal) > 0.0f) {
        outward_normal = -hit.normal;
        ni_over_nt = refraction_index;
    } else {
        outward_normal = hit.normal;
        ni_over_nt = 1.0f / refraction_index;
    }

    // Проверка на полное внутреннее отражение
    float dt = unit_direction ^ outward_normal;
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);

    if (discriminant <= 0.0f) {
        scattered = {hit.point, reflected};
        return true;
    }

    float rand_val = random01();

    // На рандомчик выбираем отражать или преломлять
    if (rand_val < reflection_coeff) {
        scattered = {hit.point, reflected};
    } else {
        Vector3d refracted = ni_over_nt * (unit_direction - outward_normal * dt) - outward_normal * std::sqrt(discriminant);
        scattered = {hit.point, refracted};
    }

    return true;
}
