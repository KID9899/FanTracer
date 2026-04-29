//
// Created by iliya on 4/23/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_LIGHTS_SKY_LIGHT_H
#define TRACER_LIGHTS_SKY_LIGHT_H


// Абсолютная компонента света (в любой точке пространства есть свет такой силы)
class SkyLight : public ILight {
    // Интенсивность в RGB
    const Vector3d intensity;
public:
    SkyLight(const Vector3d &intensity) noexcept;
    const Vector3d illuminate(const HitRecord &hit, Vector3d &light_dir, float &distance) const noexcept override;
    const Vector3d samplePoint() const noexcept override;
};


#endif // TRACER_LIGHTS_SKY_LIGHT_H
