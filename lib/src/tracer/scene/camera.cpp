//
// Created by iliya on 4/19/26.
//

#include <fstream>
#include <cmath>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <omp.h>
#include "camera.h"
#include "tracer/geometry.h"

Camera::Camera(const Vector3d &origin, const Vector3d &view, float width, float height, float angle) noexcept: origin(origin){
    Vector3d forward = view.normalize();
    Vector3d world_up = {0.f, 1.f, 0.f};

    // Что делать в случае с вертикальной камерой
    if (std::abs(world_up.cross(forward).length()) < 1e-3f) world_up = {0.f, 0.f, 1.f};

    // Пересчёт осей
    Vector3d right = forward.cross(world_up).normalize();
    Vector3d up    = right.cross(forward);

    horizontal = right * std::cos(angle) + up * std::sin(angle);
    vertical   = up    * std::cos(angle) - right * std::sin(angle);

    horizontal *= width;
    vertical   *= height;

    // Направление на левый нижний угол
    lower_left_corner = origin + forward - horizontal * 0.5f - vertical * 0.5f;
}

// TODO - Оптимизировать, добавить механику пакетов, разобраться с отладочным выводом, добавить отражение света
bool Camera::render(const Scene &scene, int width, int height, const std::string &filename, int samples_per_pixel, bool debug) const noexcept {
    // Сохранять будем в формате ppm
    std::ofstream ppm(filename);
    if (!ppm) return false;
    ppm << "P3\n" << width << " " << height << "\n255\n";

    // Размер чанка до 4096 пикселей
    constexpr int TARGET_CHUNK_PIXELS = 65536;
    int chunk_rows = std::max(1, TARGET_CHUNK_PIXELS / width);

    // lambda-функция для трассировки лучей, возвращает итоговый RGB-цвет по лучу ray
    // depth - максимальная глубина рекурсии
    std::function<Vector3d(const Ray&, int)> trace = [&](const Ray &ray, int depth) -> Vector3d {
        if (depth <= 0) return Vector3d(0, 0, 0);

        HitRecord rec;
        const float t_min = 0.001f;
        const float t_max = 1e10f;

        // собственно, фон
        if (!scene.intersect(ray, t_min, t_max, rec)) {
            return Vector3d(0, 0, 0);
        }

        // "Свечение" текстуры - безусловная составляющая света
        Vector3d color = rec.material->emitted(rec);

        // Смотрим на действия материала
        Vector3d absorption_attenuation;
        Vector3d distortion_attenuation;
        Ray scattered;

        if (rec.material->scatter(ray, rec, absorption_attenuation, distortion_attenuation, scattered)) {
            // Обработаем каждый источник света
            for (const auto &light_ptr : scene.getLights()) {
                Vector3d light_dir;
                float distance;
                Vector3d illum = light_ptr->illuminate(rec, light_dir, distance);

                // "Теневой луч" - проверка на перекрытие объекта источником света
                // TODO - добавить обратную трассировку для обеспечения особых свойств зеркал и стёкол
                Ray shadow_ray{rec.point + rec.normal * 0.0001f, light_dir};
                HitRecord shadow_rec;
                bool in_shadow = scene.intersect(shadow_ray, 0.0001f, distance - 0.0001f, shadow_rec);

                if (!in_shadow) {
                    // Коэффициент затухания
                    // TODO - сделать более реалистичным (а то как-то неестественно выглядит)
                    // TODO - добавить особые свойства света (например, ультра-яркий прожектор)
                    //  лучше для этого вынести коэффициент затухания в класс ILight
                    float ndotl = std::max(0.0f, rec.normal ^ light_dir);
                    // Учитываем прямое поглощение (цвет объекта)
                    color += absorption_attenuation * illum * ndotl;
                }
            }
            // Учитываем поглощение искажённого луча и трассируем его
            color += distortion_attenuation * trace(scattered, depth - 1);
        }
        // Вот и итоговый цвет
        return color;
    };

    for (int start_row = 0; start_row < height; start_row += chunk_rows) {
        int rows_this_chunk = std::min(chunk_rows, height - start_row);
        int current_chunk_pixels = rows_this_chunk * width;

        std::vector<Vector3d> chunk_pixels(current_chunk_pixels);

        // Параллельное вычисление пикселей чанка
        #pragma omp parallel for schedule(dynamic)
        for (int idx = 0; idx < current_chunk_pixels; ++idx) {
            auto &rng = threadRNG();
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);

            // Глобальные координаты
            int row = start_row + idx / width;
            int col = idx % width;

            // Инвертируем row
            int j = height - 1 - row;

            Vector3d pixel_color(0.0f, 0.0f, 0.0f);

            for (int s = 0; s < samples_per_pixel; ++s) {
                float u = (static_cast<float>(col) + dist(rng)) / (width  - 1);
                float v = (static_cast<float>(j)   + dist(rng)) / (height - 1);
                Ray ray = getRay(u, v);
                pixel_color += trace(ray, 50);
            }
            pixel_color /= static_cast<float>(samples_per_pixel);
            chunk_pixels[idx] = pixel_color;
        }

        // Последовательная запись чанка в файл
        for (int idx = 0; idx < current_chunk_pixels; ++idx) {
            const Vector3d &pc = chunk_pixels[idx];
            int ir = static_cast<int>(255.99f * pc.getX());
            int ig = static_cast<int>(255.99f * pc.getY());
            int ib = static_cast<int>(255.99f * pc.getZ());
            ppm << ir << " " << ig << " " << ib << "\n";
        }

        if (debug) {
            std::cerr << "\rОтрисованы строки " << start_row << "-" << (start_row + rows_this_chunk - 1) << " из " << height;
        }
    }

    if (debug) std::cerr << "\rОтрисовано " << height << " строк\nРендеринг завершён.\n";
    return true;
}
