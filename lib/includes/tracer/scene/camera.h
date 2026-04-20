//
// Created by iliya on 4/19/26.
//

#include <string>
#include "tracer/interfaces.h"
#include "tracer/geometry.h"
#include "scene.h"

#ifndef TRACER_SCENE_CAMERA_H
#define TRACER_SCENE_CAMERA_H

class Camera {
public:
    Vector3d origin;
    Vector3d lower_left_corner;
    Vector3d horizontal;
    Vector3d vertical;

    Ray getRay(float u, float v) const;
    bool render(const Scene& scene, int width, int height, const std::string& filename, int samples_per_pixel = 100) const;
};


#endif // TRACER_SCENE_CAMERA_H
