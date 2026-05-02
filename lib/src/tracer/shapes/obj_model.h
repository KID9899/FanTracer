//
// Created by iliya on 5/2/26.
//

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "tracer/interfaces/shape_group.h"
#include "tracer/materials/lambertian.h"
#include "triangle.h"

#ifndef TRACER_SHAPES_OBJ_MODEL_H
#define TRACER_SHAPES_OBJ_MODEL_H

// TODO - добавить c_api
class OBJModel : public IShapesGroup {
public:
    // Указываем файл и масштаб
    OBJModel(const std::string &file, const Vector3d &zero = {0.f, 0.f, 0.f}, const Float3 &rot = {0.f, 0.f, 0.f}, float scale = 1.0f);
    void bindMaterial(const std::string &name, const IMaterial *mat);
    void load();

private:
    const std::string filename;
    const float scale;
    const Vector3d zero;
    const Matrix3d rotation;
    std::unordered_map<std::string, const IMaterial*> materialBindings;
    // Материал по умолчанию
    std::unique_ptr<Lambertian> defaultMaterial;
    // Важно - мы владеем этими треугольниками!
    std::vector<Triangle> triangles;
};

#endif // TRACER_SHAPES_OBJ_MODEL_H
