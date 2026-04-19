//
// Created by iliya on 4/19/26.
//

#include "vector3d.h"

#ifndef TRACER_GEOMETRY_HIT_RECORD_H
#define TRACER_GEOMETRY_HIT_RECORD_H

class IMaterial;

struct HitRecord {
    float t;
    Vector3d point;
    Vector3d normal;
    const IMaterial* material;
    bool frontFace;
};

#endif // TRACER_GEOMETRY_HIT_RECORD_H
