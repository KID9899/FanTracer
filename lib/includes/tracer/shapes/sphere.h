//
// Created by iliya on 4/19/26.
//

#include <memory>
#include "tracer/interfaces.h"
#include "tracer/geometry.h"

#ifndef TRACER_SHAPES_SPHERE_H
#define TRACER_SHAPES_SPHERE_H

class Sphere : public IShape {
private:
    const Vector3d center;
    float radius;
    std::shared_ptr<IMaterial> mat;
public:
    Sphere(const Vector3d &center, float radius, std::shared_ptr<IMaterial> mat);

    bool intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const override;
    virtual AABB getBoundingBox() const override;
};

#endif // TRACER_SHAPES_SPHERE_H
