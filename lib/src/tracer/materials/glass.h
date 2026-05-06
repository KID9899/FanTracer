//
// Created by iliya on 4/19/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_MATERIALS_GLASS_H
#define TRACER_MATERIALS_GLASS_H

// Продвинутый материал с комбинированными свойствами отражения
// просвечивания с преломлением и прямого поглощения (цвета)
class Glass : public IMaterial {
    // Коэффициент преломления (прямой), например 1.52 для стекла
    const float refraction_index;
    // От 0 до 1. Чем выше - тем больше доля отражаемых лучей над преломляемыми
    const float reflection_coeff;
    // От 0 до 1. Чем выше - тем сильнее доминация прямого поглощения над искажением
    const float tint_coeff;

    // Примеры:
    // tint = 1 -> абсолютно непрозрачный материал с монотонным цветом (бетон в minecraft)
    // tint = 0, refl = 0 -> абсолютно прозрачное стекло
    // tint = 0, refl = 1 -> абсолютное зеркало
    // tint = 0.6, refl = 1 -> полированный непрозрачный драгоценный камень
    // tint = 0.6, refl = 0.5 -> яркое цветное стекло (например, бутылочное, или яркие драгоценные камни)
    // tint = 0.2, refl = 0.2 -> обычное стекло с незначительным оттенком (бледные драгоценные камни)
    // Последний вариант очень хорошо подходит для высоких коэффициентов преломления
public:
    Glass(const ITexture* tex, float ri, float refl, float tint) noexcept;
    bool scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const noexcept override;
protected:
    bool scatter_ray(const Ray& in, const HitRecord& hit, Ray& scattered) const noexcept override { return true; };
};

#endif // TRACER_MATERIALS_GLASS_H
