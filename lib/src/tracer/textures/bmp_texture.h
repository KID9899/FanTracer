//
// Created by iliya on 5/3/26.
//

#ifndef TRACER_TEXTURES_BMP_TEXTURE_H
#define TRACER_TEXTURES_BMP_TEXTURE_H

#include "tracer/textures/image_texture.h"
#include <string>

class BMPTexture : public IImageTexture {
public:
    bool load(const std::string& filename) override;
};

#endif
