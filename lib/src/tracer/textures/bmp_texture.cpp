//
// Created by iliya on 5/3/26.
//

#include "bmp_texture.h"
#include <fstream>
#include <iostream>

bool BMPTexture::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    // Заголовок BMP
    unsigned char header[54];
    file.read(reinterpret_cast<char*>(header), 54);

    int dataOffset = *(int*)&header[0x0A];
    int width      = *(int*)&header[0x12];
    int height     = *(int*)&header[0x16];
    int bitsPerPixel = *(short*)&header[0x1C];

    if (bitsPerPixel != 24) {
        std::cerr << "BMPTexture: only 24-bit BMP supported\n";
        return false;
    }

    // Пропускаем до данных
    file.seekg(dataOffset, std::ios::beg);

    // Читаем по строкам
    int rowSize = (width * 3 + 3) & ~3;
    std::vector<unsigned char> row(rowSize);
    pixels.resize(width * height);

    for (int y = 0; y < height; ++y) {
        file.read(reinterpret_cast<char*>(row.data()), rowSize);
        for (int x = 0; x < width; ++x) {
            int src = x * 3;
            unsigned char b = row[src];
            unsigned char g = row[src+1];
            unsigned char r = row[src+2];
            // Записываем в pixels строку
            pixels[y * width + x] = {r/255.f, g/255.f, b/255.f};
        }
    }

    this->width = width;
    this->height = height;
    return true;
}
