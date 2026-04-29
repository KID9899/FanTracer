//
// Created by iliya on 4/26/26.
//

#include "rotate.h"
#include "tracer/all.h"

ccls(Matrix3d) geometry_rotateAroundX(float angle) {
    return _rvtoc(Matrix3d, rotateAroundX(angle));
}
ccls(Matrix3d) geometry_rotateAroundY(float angle) {
    return _rvtoc(Matrix3d, rotateAroundY(angle));
}
ccls(Matrix3d) geometry_rotateAroundZ(float angle) {
    return _rvtoc(Matrix3d, rotateAroundZ(angle));
}
ccls(Matrix3d) geometry_eulerRotate(float rx, float ry, float rz) {
    return _rvtoc(Matrix3d, eulerRotate(rx, ry, rz));
}
ccls(Matrix3d) geometry_eulerRotateInverse(float rx, float ry, float rz) {
    return _rvtoc(Matrix3d, eulerRotateInverse(rx, ry, rz));
}
ccls(Vector3d) geometry_reflect(const ccls(Vector3d) vec, const ccls(Vector3d) axis) {
    return _rvtoc(Vector3d, reflect(_tocppci(Vector3d, vec), _tocppci(Vector3d, axis)));
}
