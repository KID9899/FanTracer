//
// Created by iliya on 5/3/26.
//

#include "tracer/interfaces.h"
#include "tracer/core.h"
#include <vector>
#include <string>
#include <algorithm>

#ifndef TRACER_TEXTURES_IMAGE_TEXTURE_H
#define TRACER_TEXTURES_IMAGE_TEXTURE_H

class IImageTexture : public ITexture {
protected:
    // Значения, которые должны переопределяться в функции load
    int width = 0, height = 0;
    std::vector<Float3> pixels;
public:
    // Функция, которая должна переопределяться в потомках
    virtual bool load(const std::string& filename) = 0;

    void get_attenuation(float u, float v, Vector3d& absorption, Vector3d& distortion) const noexcept override {
        if (width == 0 || height == 0) {
            absorption = Vector3d(0,0,0);
            distortion = Vector3d(0,0,0);
            return;
        }
        int x = (static_cast<int>(u * width) % width + width) % width;
        int y = (static_cast<int>(v * height) % height + height) % height;
        Vector3d color = pixels[y * width + x];
        absorption = color;
        distortion = color;
    }
};

#endif
