//
// Created by iliya on 4/19/26.
//

#include "mirror.h"
#include "tracer/geometry.h"

bool Mirror::scatter(const Ray &in, const HitRecord &hit, Vector3d &absorption_attenuation, Vector3d &distortion_attenuation, Ray &scattered) const noexcept {
    // Получаем отражённый луч
    Vector3d reflected = reflect(in.direction.normalize(), hit.normal);
    // Добавляем шум для размытия
    scattered = {hit.point, reflected + fuzz * randomInUnitSphere()};
    // Прямое поглощение отсутствует
    absorption_attenuation = Vector3d(0.f, 0.f, 0.f);
    distortion_attenuation = albedo;
    return (scattered.direction ^ hit.normal) > 0.f;
}

Mirror::Mirror(const Vector3d &albedo, float fuzz) noexcept: albedo(albedo), fuzz(fuzz) {}
