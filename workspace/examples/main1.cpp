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
#include "tracer/lights/sky_light.h"
#include "tracer/shapes.h"

using namespace tracer_short_names;

int main() {
    Scene scene;

    // === Материалы ===
    auto red    = std::make_shared<Lambertian>(F3{0.8f, 0.2f, 0.2f});
    auto mirror = std::make_shared<Mirror>(F3{0.95f, 0.95f, 0.95f}, 0.0f);
    auto blue_g = std::make_shared<Glass>(F3{0.5f, 0.5f, 0.8f}, 1.01f, 0.5f, 0.6f);
    auto dark_g = std::make_shared<Glass>(F3{0.5f, 0.5f, 0.5f}, 1.52f, 0.2f, 0.2f);
    auto gray   = std::make_shared<Lambertian>(F3{0.2f, 0.2f, 0.2f});
    auto green  = std::make_shared<Lambertian>(F3{0.2f, 0.8f, 0.2f});

    // Пол
    scene.add(std::make_shared<Plane>(F3{0.f,0.f,0.f}, F3{0.f,1.f,0.f}, gray));

    // Объекты
    scene.add(std::make_shared<OrientedBox>(F3{0.0f,4.33f,-2.0f}, F3{5.f,5.f,5.f}, F3{.78f, .0f, .78f}, mirror));
    scene.add(std::make_shared<Sphere>(F3{11.f,8.f,-7.f}, 8.f, mirror));
    scene.add(std::make_shared<Sphere>(F3{3.5f,0.5f,-1.f}, .5f, red));
    scene.add(std::make_shared<Cylinder>(F3{1.f,1.f,1.f}, .5f, 3.f, F3{0.3f, -2.3f, 0.f}, green));
    scene.add(std::make_shared<OrientedBox>(F3{1.4f,0.4f,11.f}, F3{2.7f,0.8f,2.f}, F3{.0f, .4f, .0f}, blue_g));
    scene.add(std::make_shared<Sphere>(F3{3.f,0.5f,13.f}, .5f, dark_g));

    // Свет
    scene.add(std::make_shared<PointLight>(F3{10.f, 10.f, 6.f}, F3{300.f, 300.f, 300.f}));

    // Камера
    Camera cam;
    cam.origin = {2.f, 1.f, 20.f};
    float viewport_height = 0.5f;
    float viewport_width = 1.0f * viewport_height;
    cam.horizontal = {viewport_width, 0.f, 0.f};
    cam.vertical   = {0.f, viewport_height, 0.f};
    cam.lower_left_corner = cam.origin
                            - cam.horizontal * 0.5f
                            - cam.vertical * 0.5f
                            - Vector3d(0.f, 0.f, 1.0f);

    cam.render(scene, 300, 300, "output.ppm", 100, true);
    return 0;
}
