//
// Created by iliya on 4/19/26.
//

#include "ray.h"

const Vector3d Ray::at(float t) const {
    return origin + t * direction;
}
