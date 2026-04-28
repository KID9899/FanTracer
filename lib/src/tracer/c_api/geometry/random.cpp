//
// Created by iliya on 4/26/26.
//

#include "random.h"
#include "tracer/geometry.h"
#include "tracer/core.h"

ccls(Vector3d) geometry_randomInUnitSphere() {
    return _rvtoc(Vector3d, randomInUnitSphere());
}
