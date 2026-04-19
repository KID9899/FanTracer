//
// Created by iliya on 4/19/26.
//

#include <fstream>
#include <cmath>
#include <iostream>
#include <functional>
#include "camera.h"

Ray Camera::getRay(float u, float v) const {
    Vector3d dir = lower_left_corner + u * horizontal + v * vertical - origin;
    return {origin, dir};
}

bool Camera::render(const Scene &scene, int width, int height, const std::string &filename) const {
    std::ofstream ppm(filename);
    if (!ppm) {
        return false;
    }

    ppm << "P3\n" << width << " " << height << "\n255\n";

    std::function<Vector3d(const Ray&, int)> trace = [&](const Ray& ray, int depth) -> Vector3d {
        if (depth <= 0) return Vector3d(0, 0, 0);

        HitRecord rec;
        const float t_min = 0.001f;
        const float t_max = 1e10f;

        if (!scene.intersect(ray, t_min, t_max, rec)) {
            return Vector3d(0, 0, 0);
        }

        Vector3d color = rec.material->emitted(rec, rec.point);

        Vector3d absorption_attenuation;
        Vector3d distortion_attenuation;
        Ray scattered;
        if (rec.material->scatter(ray, rec, absorption_attenuation, distortion_attenuation, scattered)) {
            for (const auto& light_ptr : scene.getLights()) {
                Vector3d light_dir;
                float distance;
                Vector3d illum = light_ptr->illuminate(rec, light_dir, distance);

                Ray shadow_ray{rec.point + rec.normal * 0.0001f, light_dir};
                HitRecord shadow_rec;
                bool in_shadow = scene.intersect(shadow_ray, 0.0001f, distance - 0.0001f, shadow_rec);

                if (!in_shadow) {
                    float ndotl = std::max(0.0f, rec.normal * light_dir);

                    color += (absorption_attenuation ^ illum) * ndotl;
                }
            }

            color += distortion_attenuation ^ trace(scattered, depth - 1);
        }

        return color;
    };

    for (int j = height - 1; j >= 0; --j) {
        std::cout << "\rСканирование строк: " << (height - j) << " / " << height << std::flush;
        for (int i = 0; i < width; ++i) {
            float u = static_cast<float>(i) / (width - 1);
            float v = static_cast<float>(j) / (height - 1);

            Ray ray = getRay(u, v);
            Vector3d color = trace(ray, 50);
            int ir = static_cast<int>(255.99f * color.getX());
            int ig = static_cast<int>(255.99f * color.getY());
            int ib = static_cast<int>(255.99f * color.getZ());
            ppm << ir << " " << ig << " " << ib << "\n";
        }
    }
    return true;
}