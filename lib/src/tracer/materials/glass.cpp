//
// Created by iliya on 4/19/26.
//

#include <cmath>
#include "glass.h"
#include "tracer/geometry.h"

Glass::Glass(const ITexture* tex, float ri, float refl, float tint) noexcept
        : IMaterial(tex), refraction_index(ri), reflection_coeff(refl), tint_coeff(tint) {}

// Полностью переопределяем scatter
bool Glass::scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption, Vector3d& distortion, Ray& scattered) const noexcept {
    Vector3d unit_direction = in.direction.normalize();
    Vector3d reflected = reflect(unit_direction, hit.normal);

    // Получаем цвет из текстуры
    Vector3d texAbsorption, texDistortion;
    texture->get_attenuation(hit.u, hit.v, texAbsorption, texDistortion);

    // Рассчитываем поглощения из коэффициентов
    Vector3d white(1.0f, 1.0f, 1.0f);
    absorption = Vector3d(0.f, 0.f, 0.f);
    distortion = white * (1.0f - tint_coeff) + texDistortion * tint_coeff;

    // Ищем преломление и отражение
    Vector3d outward_normal;
    float ni_over_nt;
    if ((unit_direction ^ hit.normal) > 0.0f) {
        outward_normal = -hit.normal;
        ni_over_nt = refraction_index;
    } else {
        outward_normal = hit.normal;
        ni_over_nt = 1.0f / refraction_index;
    }

    float dt = unit_direction ^ outward_normal;
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);

    // Если наблюдается полное внутреннее отражение
    if (discriminant <= 0.0f) {
        scattered = {hit.point, reflected};
        return true;
    }

    // Выбираем отразить или преломить
    float rand_val = random01();
    if (rand_val < reflection_coeff) {
        scattered = {hit.point, reflected};
    } else {
        Vector3d refracted = ni_over_nt * (unit_direction - outward_normal * dt) - outward_normal * std::sqrt(discriminant);
        scattered = {hit.point, refracted};
    }
    return true;
}
