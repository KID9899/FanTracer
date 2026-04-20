//
// Created by iliya on 4/19/26.
//

#include <fstream>
#include <cmath>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <ctime>
#include "camera.h"

Ray Camera::getRay(float u, float v) const {
    Vector3d dir = lower_left_corner + u * horizontal + v * vertical - origin;
    return {origin, dir};
}

// TODO - Написать комментарии, добавить поддержку актуальных методов, оптимизировать, добавить SIMD-архитектуру, механику пакетов, разобраться с отладочным выводом
bool Camera::render(const Scene &scene, int width, int height, const std::string &filename, int samples_per_pixel) const {
    std::ofstream ppm(filename);
    if (!ppm) return false;

    ppm << "P3\n" << width << " " << height << "\n255\n";

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::function<Vector3d(const Ray&, int)> trace = [&](const Ray& ray, int depth) -> Vector3d {
        if (depth <= 0) return Vector3d(0, 0, 0);

        HitRecord rec;
        const float t_min = 0.001f;
        const float t_max = 1e10f;

        if (!scene.intersect(ray, t_min, t_max, rec)) {
            return Vector3d(0, 0, 0);
        }

        Vector3d color = rec.material->emitted(rec);

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
            Vector3d pixel_color(0, 0, 0);

            for (int s = 0; s < samples_per_pixel; ++s) {
                float u = (static_cast<float>(i) + (std::rand() / (RAND_MAX + 1.0f))) / (width - 1);
                float v = (static_cast<float>(j) + (std::rand() / (RAND_MAX + 1.0f))) / (height - 1);

                Ray ray = getRay(u, v);
                pixel_color += trace(ray, 50);
            }

            pixel_color /= static_cast<float>(samples_per_pixel);

            int ir = static_cast<int>(255.99f * pixel_color.getX());
            int ig = static_cast<int>(255.99f * pixel_color.getY());
            int ib = static_cast<int>(255.99f * pixel_color.getZ());
            ppm << ir << " " << ig << " " << ib << "\n";
        }
    }
    return true;
}
