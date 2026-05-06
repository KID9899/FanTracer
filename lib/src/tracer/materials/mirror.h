//
// Created by iliya on 4/19/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_MATERIALS_MIRROR_H
#define TRACER_MATERIALS_MIRROR_H

class Mirror : public IMaterial {
    // Размытие в зеркале
    const float fuzz;
    // 1 - коэффициент отражения по трём цветам
    // Чем меньше коэффициент отражения (чем больше inv_albedo), тем сильнее проявляется текстура
    const Vector3d inv_albedo;
public:
    inline Mirror(const ITexture* tex, float fuzz, const Vector3d& albedo) noexcept : IMaterial(tex), fuzz(fuzz), inv_albedo(Vector3d(1.f) - albedo) {}
    bool scatter_ray(const Ray& in, const HitRecord& hit, Ray& scattered) const noexcept override;
    void modify_attenuation(Vector3d& absorption, Vector3d& distortion) const noexcept override;
};


#endif // TRACER_MATERIALS_MIRROR_H
