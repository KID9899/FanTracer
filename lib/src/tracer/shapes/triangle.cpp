//
// Created by iliya on 5/2/26.
//

#include "triangle.h"
#include <cmath>

Triangle::Triangle(const Vector3d &a, const Vector3d &b, const Vector3d &c, const IMaterial *m) noexcept
        : v0(a), v1(b), v2(c), normal((v1 - v0).cross(v2 - v0).normalize()), mat(m),
          uv0{0,0}, uv1{0,0}, uv2{0,0}, hasUV(false) {}

Triangle::Triangle(const Vector3d &a, const Vector3d &b, const Vector3d &c,
                   const Float2 &uva, const Float2 &uvb, const Float2 &uvc,
                   const IMaterial *m) noexcept
        : v0(a), v1(b), v2(c), normal((v1 - v0).cross(v2 - v0).normalize()), mat(m),
          uv0(uva), uv1(uvb), uv2(uvc), hasUV(true) {}

bool Triangle::intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const noexcept {
    constexpr float EPS = 1e-7f;

    Vector3d edge1 = v1 - v0;
    Vector3d edge2 = v2 - v0;
    Vector3d h = ray.direction.cross(edge2);
    float a = edge1 ^ h;
    if (std::abs(a) < EPS) return false;

    float f = 1.0f / a;
    Vector3d s = ray.origin - v0;
    float u = f * (s ^ h);   // барицентрическое u
    if (u < 0.0f || u > 1.0f) return false;

    Vector3d q = s.cross(edge1);
    float v = f * (ray.direction ^ q); // барицентрическое v
    if (v < 0.0f || u + v > 1.0f) return false;

    float t = f * (edge2 ^ q);
    if (t < t_min || t > t_max) return false;

    hit.t = t;
    hit.point = ray.at(t);
    hit.normal = normal;
    hit.material = mat;
    hit.frontFace = (ray.direction ^ normal) < 0.0f;

    if (hasUV) {
        float w = 1.0f - u - v;
        hit.u = w * uv0.u + u * uv1.u + v * uv2.u;
        hit.v = w * uv0.v + u * uv1.v + v * uv2.v;
    } else {
        hit.u = 0.f;
        hit.v = 0.f;
    }

    return true;
}

AABB Triangle::getBoundingBox() const noexcept {
    auto minmax = [](float x, float y, float z, float &minVal, float &maxVal) {
        minVal = std::min(std::min(x, y), z);
        maxVal = std::max(std::max(x, y), z);
    };
    float minX, maxX, minY, maxY, minZ, maxZ;
    minmax(v0.getX(), v1.getX(), v2.getX(), minX, maxX);
    minmax(v0.getY(), v1.getY(), v2.getY(), minY, maxY);
    minmax(v0.getZ(), v1.getZ(), v2.getZ(), minZ, maxZ);
    return {Vector3d(minX, minY, minZ), Vector3d(maxX, maxY, maxZ)};
}
