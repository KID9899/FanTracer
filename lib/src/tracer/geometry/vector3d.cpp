//
// Created by iliya on 4/18/26.
//

#include <cmath>
#include "vector3d.h"

#ifdef LIBRARY_BUILDING
#include "c_api/geometry/vector3d.hpp"
#endif

AllowCopyImpl(Vector3d);
AllowMoveImpl(Vector3d);
DestructorImpl(Vector3d);

Vector3d::Vector3d(float x, float y, float z) noexcept: x(x), y(y), z(z) {}

float Vector3d::getX() const {
    return x;
}

float Vector3d::getY() const {
    return y;
}

float Vector3d::getZ() const {
    return z;
}

Vector3d &Vector3d::operator+=(const Vector3d &other) noexcept {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3d &Vector3d::operator-=(const Vector3d &other) noexcept {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3d &Vector3d::operator^=(const Vector3d &other) noexcept {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

float Vector3d::operator*(const Vector3d &other) const noexcept {
    return x * other.x + y * other.y + z * other.z;
}

Vector3d &Vector3d::operator*=(float scalar) noexcept {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3d &Vector3d::operator/=(float scalar) noexcept {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

Vector3d Vector3d::operator-() const noexcept {
    return Vector3d(-x, -y, -z);
}

float Vector3d::hypot() const noexcept {
    return x * x + y * y + z * z;
}

float Vector3d::length() const noexcept {
    return sqrt(hypot());
}

Vector3d Vector3d::normalize() const noexcept {
    float l = length();
    if (l == 0) {
        return Vector3d(x, y, z);
    }
    return Vector3d(x / l, y / l, z / l);
}

Vector3d Vector3d::reflect(const Vector3d &axis) const noexcept {
    return (*this) - 2 * (((*this) * axis) / (axis * axis)) * axis;
}

DefaultBinOpImpl(Vector3d, +)
DefaultBinOpImpl(Vector3d, -)
DefaultBinOpImpl(Vector3d, ^)

LeftBinOpImpl(Vector3d, float, *)
LeftBinOpImpl(Vector3d, float, /)

CommutativeOpImpl(Vector3d, Vector3d, float, *)
