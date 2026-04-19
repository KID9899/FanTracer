//
// Created by iliya on 4/18/26.
//

#include "vector3d.h"

Vector3d::Vector3d(double x, double y, double z) noexcept: x(x), y(y), z(z) {}

double Vector3d::getX() const {
    return x;
}

double Vector3d::getY() const {
    return y;
}

double Vector3d::getZ() const {
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

double Vector3d::operator*(const Vector3d &other) const noexcept {
    return x * other.x + y * other.y + z * other.z;
}

Vector3d &Vector3d::operator*=(double scalar) noexcept {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3d Vector3d::operator-() const noexcept {
    return Vector3d(-x, -y, -z);
}
