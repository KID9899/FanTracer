//
// Created by iliya on 4/17/26.
//
#include <iostream>
#include "tracer/geometry.h"
#include "tracer/scene.h"
#include "tracer/materials/lambertian.h"
#include "tracer/materials/mirror.h"
#include "tracer/materials/glass.h"
#include "tracer/lights/point_light.h"
#include "tracer/shapes.h"

int main() {
    Scene scene;

    // === Материалы ===
    auto red    = std::make_shared<Lambertian>(Vector3d(0.8f, 0.2f, 0.2f));
    auto mirror = std::make_shared<Mirror>(Vector3d(0.95f, 0.95f, 0.95f), 0.0f);
    auto blue_g = std::make_shared<Glass>(Vector3d(0.5f, 0.5f, 0.8f), 1.01f, 0.5f, 0.6f);
    auto dark_g = std::make_shared<Glass>(Vector3d(0.5f, 0.5f, 0.5f), 1.52f, 0.2f, 0.2f);
    auto gray   = std::make_shared<Lambertian>(Vector3d(0.2f, 0.2f, 0.2f));
    auto green  = std::make_shared<Lambertian>(Vector3d(0.2f, 0.8f, 0.2f));

    // Пол
    scene.add(std::make_shared<Plane>(Vector3d(0,0,0), Vector3d(0,1,0), gray));

    // Объекты


    // Свет
    scene.add(std::make_shared<PointLight>(Vector3d(10.0f, 10.0f, 6.0f), Vector3d(300, 300, 300)));

    // Камера
    Camera cam;
    cam.origin = Vector3d(2.0, 1.0f, 20.0f);
    float viewport_height = 0.5f;
    float viewport_width = 1.0f * viewport_height;
    cam.horizontal = Vector3d(viewport_width, 0, 0);
    cam.vertical   = Vector3d(0, viewport_height, 0);
    cam.lower_left_corner = cam.origin
                            - cam.horizontal * 0.5f
                            - cam.vertical * 0.5f
                            - Vector3d(0, 0, 1.0f);

    cam.render(scene, 300, 300, "output.ppm", 100);
    return 0;
}
