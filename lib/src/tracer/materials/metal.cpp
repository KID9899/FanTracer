//
// Created by iliya on 4/19/26.
//

#include "metal.h"

bool Metal::scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const  {
    Vector3d reflected = in.direction.normalize().reflect(hit.normal);
    scattered = {hit.point, reflected + fuzz * randomInUnitSphere()};
    absorption_attenuation = Vector3d(0.0f, 0.0f, 0.0f);
    distortion_attenuation = albedo;
    return scattered.direction * hit.normal > 0;
}

Metal::Metal(const Vector3d &albedo, float fuzz): albedo(albedo), fuzz(fuzz) {}
