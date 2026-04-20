//
// Created by iliya on 4/19/26.
//

#include "mirror.h"

bool Mirror::scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const  {
    // Получаем отражённый луч
    Vector3d reflected = in.direction.normalize().reflect(hit.normal);
    // Добавляем шум для размытия
    scattered = {hit.point, reflected + fuzz * randomInUnitSphere()};
    // Прямое поглощение отсутствует
    absorption_attenuation = Vector3d(0.0f, 0.0f, 0.0f);
    distortion_attenuation = albedo;
    return scattered.direction * hit.normal > 0;
}

Mirror::Mirror(const Vector3d &albedo, float fuzz): albedo(albedo), fuzz(fuzz) {}
