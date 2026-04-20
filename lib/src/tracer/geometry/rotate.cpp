//
// Created by iliya on 4/20/26.
//

#include <cmath>
#include "rotate.h"

Vector3d rotateAroundX(const Vector3d& v, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    float y = v.getY() * c - v.getZ() * s;
    float z = v.getY() * s + v.getZ() * c;
    return Vector3d(v.getX(), y, z);
}

Vector3d rotateAroundY(const Vector3d& v, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    float x = v.getX() * c + v.getZ() * s;
    float z = -v.getX() * s + v.getZ() * c;
    return Vector3d(x, v.getY(), z);
}

Vector3d rotateAroundZ(const Vector3d& v, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    float x = v.getX() * c - v.getY() * s;
    float y = v.getX() * s + v.getY() * c;
    return Vector3d(x, y, v.getZ());
}

Vector3d eulerRotate(const Vector3d& v, float rx, float ry, float rz) {
    Vector3d temp = rotateAroundX(v, rx);
    temp = rotateAroundY(temp, ry);
    temp = rotateAroundZ(temp, rz);
    return temp;
}

Vector3d eulerRotateInverse(const Vector3d& v, float rx, float ry, float rz) {
    Vector3d temp = rotateAroundZ(v, -rz);
    temp = rotateAroundY(temp, -ry);
    temp = rotateAroundX(temp, -rx);
    return temp;
}
