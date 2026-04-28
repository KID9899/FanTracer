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

Camera::Camera(const Vector3d &origin, const Vector3d &view, float width, float height, float angle): origin(origin){
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

Ray Camera::getRay(float u, float v) const {
    Vector3d dir = lower_left_corner + u * horizontal + v * vertical - origin;
    return {origin, dir};
}

// TODO - Оптимизировать, добавить механику пакетов, разобраться с отладочным выводом, добавить отражение света
bool Camera::render(const Scene &scene, int width, int height, const std::string &filename, int samples_per_pixel, bool debug) const {
    // Сохранять будем в формате ppm
    std::ofstream ppm(filename);
    if (!ppm) return false;
    ppm << "P3\n" << width << " " << height << "\n255\n";

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // lambda-функция для трассировки лучей, возвращает итоговый RGB-цвет по лучу ray
    // depth - максимальная глубина рекурсии
    std::function<Vector3d(const Ray&, int)> trace = [&](const Ray& ray, int depth) -> Vector3d {
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
            for (const auto& light_ptr : scene.getLights()) {
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

    Vector3d pixels[width*height];

    // Параллельная обработка пикселей
    #pragma omp parallel for schedule(dynamic) collapse(2)
    for (int j = 0; j < height; ++j) {
        // Локальный для потока генератор случайных чисел
        thread_local std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        for (int i = 0; i < width; ++i) {
            Vector3d pixel_color(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < samples_per_pixel; ++s) {
                float u = (static_cast<float>(i) + dist(gen)) / (width - 1);
                float v = (static_cast<float>(j) + dist(gen)) / (height - 1);
                Ray ray = getRay(u, v);
                pixel_color += trace(ray, 50);
            }
            pixel_color /= static_cast<float>(samples_per_pixel);
            // Сохраняем в буфер (индекс с учётом переворота по вертикали,
            // т.к. в исходном коде цикл шёл от height-1 до 0,
            // здесь j идёт от 0, поэтому для правильного порядка в файле
            // инвертируем j: строки снизу вверх.
            int row = height - 1 - j;
            pixels[row * width + i] = pixel_color;
        }
    }

    // Отладочный вывод теперь не нужен внутри цикла, можно вывести один раз
    if (debug) std::cout << "Рендеринг завершён.\n";

    // Последовательная запись файла
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            const Vector3d& pc = pixels[row * width + col];
            int ir = static_cast<int>(255.99f * pc.getX());
            int ig = static_cast<int>(255.99f * pc.getY());
            int ib = static_cast<int>(255.99f * pc.getZ());
            ppm << ir << " " << ig << " " << ib << "\n";
        }
    }

    return true;
    return true;
}
