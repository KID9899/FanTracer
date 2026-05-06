//
// Created by iliya on 4/19/26.
//

#include "lambertian.h"
#include "tracer/geometry.h"

bool Lambertian::scatter_ray(const Ray& in, const HitRecord& hit, Ray& scattered) const noexcept {
    scattered = {hit.point, hit.normal + randomInUnitSphere()};
    return true;
}
