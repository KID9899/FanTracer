//
// Created by iliya on 4/18/26.
//

#include "funny_defines/classes.h"

#ifndef TRACER_GEOMETRY_VECTOR3D_H
#define TRACER_GEOMETRY_VECTOR3D_H

class Vector3d {
private:
    float x, y, z;
public:
    AllowCopyDecl(Vector3d);
    AllowMoveDecl(Vector3d);
    DestructorDecl(Vector3d);

    Vector3d(float x = 0, float y = 0, float z = 0) noexcept;

    float getX() const;
    float getY() const;
    float getZ() const;

    Vector3d& operator+=(const Vector3d& other) noexcept;
    Vector3d& operator-=(const Vector3d& other) noexcept;
    Vector3d& operator^=(const Vector3d& other) noexcept;
    Vector3d& operator*=(float scalar) noexcept;
    Vector3d& operator/=(float scalar) noexcept;

    float operator*(const Vector3d& other) const noexcept;

    Vector3d operator-() const noexcept;

    float hypot() const noexcept;
    float length() const noexcept;

    Vector3d normalize() const noexcept;
    Vector3d reflect(const Vector3d& axis) const noexcept;
};

DefaultBinOpDecl(Vector3d, +)
DefaultBinOpDecl(Vector3d, -)
DefaultBinOpDecl(Vector3d, ^)

LeftBinOpDecl(Vector3d, float, *)
LeftBinOpDecl(Vector3d, float, /)

CommutativeOpDecl(Vector3d, Vector3d, float, *)

#endif // TRACER_GEOMETRY_VECTOR3D_H
