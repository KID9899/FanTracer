//
// Created by iliya on 4/19/26.
//

#include "tracer/core.h"
#include "tracer/structs.h"
#include "texture.h"

#ifndef TRACER_INTERFACES_MATERIAL_H
#define TRACER_INTERFACES_MATERIAL_H

class IMaterial {
protected:
    const ITexture* texture;
public:
    IMaterial(const ITexture* tex) noexcept : texture(tex) {}
    virtual ~IMaterial() = default;

    // Производит взаимодействие луча с телом
    // Ввод:
    //   in - луч, пересекшийся с телом
    //   hit - информация о пересечении
    // Вывод:
    //   absorption_attenuation - прямое поглощение (поглощение луча, отражённого в камеру)
    //   distortion_attenuation - поглощение искажённого луча (затцхание при отражении, просвете и так далее)
    //   scattered - луч, получившийся после "столкновения" луча in с материалом
    virtual bool scatter(const Ray& in, const HitRecord& hit, Vector3d& absorption_attenuation, Vector3d& distortion_attenuation, Ray& scattered) const noexcept {
        if (!scatter_ray(in, hit, scattered)) return false;
        texture->get_attenuation(hit.u, hit.v, absorption_attenuation, distortion_attenuation);
        modify_attenuation(absorption_attenuation, distortion_attenuation);
        return true;
    }

    // Постоянная цветовая компонента (например, цвет свечения светящихся текстур или голограмм)
    virtual const Vector3d emitted(const HitRecord& hit) const noexcept {
        return texture->emitted(hit.u, hit.v);
    }

protected:
    // Переопределяется в конкретных материалах, определяет направление искажённого луча
    virtual bool scatter_ray(const Ray& in, const HitRecord& hit, Ray& scattered) const noexcept = 0;

    // Возможность изменить поглощение после получения от текстуры
    virtual void modify_attenuation(Vector3d& absorption, Vector3d& distortion) const noexcept {}
};

#endif
