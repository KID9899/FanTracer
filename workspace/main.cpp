//
// Created by iliya on 4/17/26.
//
#include <iostream>
#include "tracer/geometry.h"
#include "tracer/scene.h"
#include "tracer/materials/lambertian.h"
#include "tracer/materials/metal.h"
#include "tracer/materials/glass.h"
#include "tracer/lights/point_light.h"
#include "tracer/shapes/sphere.h"

int main() {
    Scene scene;

    // === Материалы ===
    auto red_diffuse = std::make_shared<Lambertian>(Vector3d(0.8f, 0.2f, 0.2f));
    auto mirror      = std::make_shared<Metal>(Vector3d(0.95f, 0.95f, 0.95f), 0.0f);
    auto glass       = std::make_shared<Glass>(Vector3d(0.5f, 0.5f, 0.5f), 1.01f, 0.05f, 0.6f);
    auto floor_mat   = std::make_shared<Lambertian>(Vector3d(0.2f, 0.8f, 0.2f));

    // === Объекты ===
    scene.add(std::make_shared<Sphere>(Vector3d(-0.5f, 0.5f,  1.0f),  0.5f, red_diffuse));
    scene.add(std::make_shared<Sphere>(Vector3d( 0.8f, 2.0f, -2.0f),  2.0f, mirror));
    scene.add(std::make_shared<Sphere>(Vector3d( 0.4f, 1.0f, 4.0f),  0.4f, glass));

    // Пол
    scene.add(std::make_shared<Sphere>(Vector3d(0, -100.5f, 0), 100.0f, floor_mat));

    // Свет
    scene.add(std::make_shared<PointLight>(Vector3d(0, 5.0f, 2.0f), Vector3d(20, 20, 20)));
    scene.add(std::make_shared<PointLight>(Vector3d(0, 1.0f, -7.0f), Vector3d(20, 20, 20)));

    // Камера
    Camera cam;
    cam.origin = Vector3d(0, 1.0f, 5.0f);
    float viewport_height = 3.0f;
    float viewport_width = 16.0f / 9.0f * viewport_height;
    cam.horizontal = Vector3d(viewport_width, 0, 0);
    cam.vertical   = Vector3d(0, viewport_height, 0);
    cam.lower_left_corner = cam.origin
                            - cam.horizontal * 0.5f
                            - cam.vertical * 0.5f
                            - Vector3d(0, 0, 1.0f);

    cam.render(scene, 2048, 1152, "output.ppm");
    return 0;
}