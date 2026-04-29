//
// Created by iliya on 4/19/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_LIGHTS_POINT_LIGHT_H
#define TRACER_LIGHTS_POINT_LIGHT_H


// Классический точечный источник света
class PointLight : public ILight {
    // Координаты источника
    const Vector3d position;
    // Интенсивность в RGB
    const Vector3d intensity;
public:
    PointLight(const Vector3d &position, const Vector3d &intensity) noexcept;
    const Vector3d illuminate(const HitRecord &hit, Vector3d &light_dir, float &distance) const noexcept override;
    const Vector3d samplePoint() const noexcept override;
};


#endif // TRACER_LIGHTS_POINT_LIGHT_H
