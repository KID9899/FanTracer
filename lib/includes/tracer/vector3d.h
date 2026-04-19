//
// Created by iliya on 4/18/26.
//

#include "funny_defines/classes.h"

#pragma once

class Vector3d {
private:
    double x, y, z;
public:
    AllowCopy(Vector3d);
    AllowMove(Vector3d);
    Destructor(Vector3d);

    Vector3d(double x = 0, double y = 0, double z = 0) noexcept;

    double getX() const;
    double getY() const;
    double getZ() const;

    Vector3d& operator+=(const Vector3d& other) noexcept;
    Vector3d& operator-=(const Vector3d& other) noexcept;
    Vector3d& operator*=(double scalar) noexcept;

    double operator*(const Vector3d& other) const noexcept;

    Vector3d operator-() const noexcept;
};

DefaultBinOp(Vector3d, +)
DefaultBinOp(Vector3d, -)

LeftBinOp(Vector3d, double, *)

CommutativeOp(Vector3d, Vector3d, double, *)

#include "c_api/vector3d.hpp"
