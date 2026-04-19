//
// Created by iliya on 4/19/26.
//

#include "vector3d.h"
#include "funny_defines/classes.h"

#ifndef TRACER_GEOMETRY_RAY_H
#define TRACER_GEOMETRY_RAY_H

struct Ray {
    Vector3d origin;
    Vector3d direction;

    const Vector3d at(float t) const;
};

#endif // TRACER_GEOMETRY_RAY_H
