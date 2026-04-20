//
// Created by iliya on 4/20/26.
//

#include <memory>
#include "tracer/interfaces.h"
#include "tracer/geometry.h"

#ifndef TRACER_SHAPES_CYLINDER_H
#define TRACER_SHAPES_CYLINDER_H

class Cylinder : public IShape {
    Vector3d center;
    float radius;
    float height;
    Vector3d rotation;
    std::shared_ptr<IMaterial> mat;
public:
    Cylinder(const Vector3d& c, float r, float h, const Vector3d& rot, std::shared_ptr<IMaterial> m);

    bool intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const override;
    AABB getBoundingBox() const override;
};

#endif // TRACER_SHAPES_CYLINDER_H
