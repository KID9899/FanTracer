//
// Created by iliya on 4/17/26.
//
#include <iostream>
#include "tracer/c_api/vector3d.hpp"

int main() {
    ccls(Vector3d) a = Vector3d_make(1.0, 2.0, 3.0);
    ccls(Vector3d) b = Vector3d_make(4.0, 5.0, 6.0);

    ccls(Vector3d) c = Vector3d_add_op(a, b);

    printf("%f, %f, %f\n", Vector3d_getX(c), Vector3d_getY(c), Vector3d_getZ(c));
}