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
    scene.add(std::make_shared<OrientedBox>(Vector3d(0.0f,4.33f,-2.0f), Vector3d(5,5,5), Vector3d(0.78f, 0.0f, 0.78f), mirror));
    scene.add(std::make_shared<Sphere>(Vector3d(11.0f,8.0f,-7.0f), 8.0f, mirror));
    scene.add(std::make_shared<Sphere>(Vector3d(3.5f,0.5f,-1.0f), 0.5, red));
    scene.add(std::make_shared<OrientedBox>(Vector3d(1.0f,1.0f,1.0f), Vector3d(1,3,1), Vector3d(0.3f, -2.3f, 0.0f), green));
    scene.add(std::make_shared<OrientedBox>(Vector3d(1.4f,0.4f,11.0f), Vector3d(2.7,0.8,2), Vector3d(0.0f, 0.4f, 0.0f), blue_g));
    scene.add(std::make_shared<Sphere>(Vector3d(3.0f,0.5f,13.0f), 0.5f, dark_g));

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

    cam.render(scene, 2048, 2048, "output.ppm", 100);
    return 0;
}
