//
// Created by iliya on 4/19/26.
//

#include "mirror.h"
#include "tracer/geometry.h"

bool Mirror::scatter_ray(const Ray& in, const HitRecord& hit, Ray& scattered) const noexcept {
    Vector3d reflected = reflect(in.direction.normalize(), hit.normal);
    scattered = {hit.point, reflected + fuzz * randomInUnitSphere()};
    return (scattered.direction ^ hit.normal) > 0.f;
}

void Mirror::modify_attenuation(Vector3d& absorption, Vector3d& distortion) const noexcept {
    absorption *= inv_albedo;
}
