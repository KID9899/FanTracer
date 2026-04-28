//
// Created by iliya on 4/19/26.
//

#include <string>
#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"
#include "scene.h"

#ifndef TRACER_SCENE_CAMERA_H
#define TRACER_SCENE_CAMERA_H

class Camera {
    // Точка в которой располагается камера
    Vector3d origin;
    // Направление на нижний левый угол
    Vector3d lower_left_corner;
    // Размеры угла обзора в радианах
    Vector3d horizontal;
    Vector3d vertical;
public:
    Camera(const Vector3d &origin, const Vector3d &view, float horizontal, float vertical, float angle = 0.f);
    // Возвращает луч для пикселя по координатам [U, V] (от 0 до 1 по вертикали и горизонтали от левого нижнего угла)
    Ray getRay(float u, float v) const;
    // Отрисовать сцену scene и сохранить в файл filename (размеры итогового изображения width*height)
    // samples_per_pixel - показатель сколько вариантов лучей будет рассчитано для каждого пикселя (чем выше - тем более чётко будут отрисовываться маловероятные события, например отражение в стекле)
    // debug - выводить отладочную информацию (процесс обработки изображения по строкам)
    bool render(const Scene& scene, int width, int height, const std::string& filename, int samples_per_pixel = 100, bool debug = false) const;
};


#endif // TRACER_SCENE_CAMERA_H
