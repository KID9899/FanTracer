//
// Created by iliya on 4/19/26.
//

#include "tracer/interfaces.h"
#include "tracer/geometry.h"

#ifndef TRACER_MATERIALS_GLASS_H
#define TRACER_MATERIALS_GLASS_H

// Продвинутый материал с комбинированными свойствами отражения
// просвечивания с преломлением и прямого поглощения (цвета)
class Glass : public IMaterial {
    // Цвет материала
    Vector3d color;
    // Коэффициент преломления (прямой), например 1.52 для стекла
    float refraction_index;
    // От 0 до 1. Чем выше - тем больше доля отражаемых лучей над преломляемыми
    float reflection_coeff;
    // От 0 до 1. Чем выше - тем сильнее доминация прямого поглощения над искажением
    float tint_coeff;

    // Примеры:
    // tint = 1 -> абсолютно непрозрачный материал с монотонным цветом (бетон в minecraft)
    // tint = 0, refl = 0 -> абсолютно прозрачное стекло
    // tint = 0, refl = 1 -> абсолютное зеркало
    // tint = 0.6, refl = 1 -> полированный непрозрачный драгоценный камень
    // tint = 0.6, refl = 0.5 -> яркое цветное стекло (например, бутылочное, или яркие драгоценные камни)
    // tine = 0.2, refl = 0.2 -> обычное стекло с незначительным оттенком (бледные драгоценные камни)
    // Последний вариант очень хорошо подходит для высоких коэффициентов преломления
public:
    Glass(const Vector3d& color, float ri, float refl, float tint);

    bool scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const override;
};

#endif // TRACER_MATERIALS_GLASS_H
