//
// Created by iliya on 4/20/26.
//

#include <memory>
#include "tracer/interfaces.h"
#include "tracer/geometry.h"

#ifndef TRACER_SHAPES_PLANE_H
#define TRACER_SHAPES_PLANE_H

class Plane : public IShape {
    Vector3d point;
    Vector3d normal;
    std::shared_ptr<IMaterial> mat;
public:
    Plane(const Vector3d& p, const Vector3d& n, std::shared_ptr<IMaterial> m);

    bool intersect(const Ray& ray, float t_min, float t_max, HitRecord& hit) const override;
    AABB getBoundingBox() const override;
};

#endif // TRACER_SHAPES_PLANE_H
