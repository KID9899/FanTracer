//
// Created by iliya on 5/2/26.
//

#include "tracer/geometry.h"
#include "obj_model.h"
#include <fstream>
#include <sstream>
#include <iostream>

OBJModel::OBJModel(const std::string &file, const Vector3d& zero, const Float3 &rot, float scale): filename(file), scale(scale),
        zero(zero), rotation(eulerRotate(rot.x, rot.y, rot.z)),
        defaultMaterial(std::make_unique<Lambertian>(Vector3d(0.5f, 0.0f, 0.5f))) {}

void OBJModel::bindMaterial(const std::string &name, const IMaterial *mat) {
    materialBindings[name] = mat;
}

void OBJModel::load() {
    // Собственно, открываем файлик
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "OBJModel: cannot open " << filename << std::endl;
        return;
    }

    // Список позиций точек
    std::vector<Vector3d> positions;
    std::string line;
    const IMaterial *currentMaterial = defaultMaterial.get();

    // Список индексов вершин наших треугольников
    struct Triplet { int v1, v2, v3; };
    std::vector<Triplet> faceTriplets;

    while (std::getline(in, line)) {

        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token == "v") {
            // В случае, если вводится новая точка
            float x, y, z;
            if (iss >> x >> y >> z)
                positions.push_back(rotation.apply(Vector3d(x, y, z)) * scale + zero);
        } else if (token == "f") {
            // Если делается некоторая поверхность
            std::vector<int> verts;
            std::string vtx;
            while (iss >> vtx) {
                std::istringstream vss(vtx);
                std::string indexStr;
                std::getline(vss, indexStr, '/');
                int idx = std::stoi(indexStr);
                if (idx > 0) verts.push_back(idx);
                else std::cerr << "OBJModel: negative indices unsupported\n";
            }
            if (verts.size() == 3) {
                // Это треугольник (кайф)
                faceTriplets.push_back({verts[0], verts[1], verts[2]});
            } else if (verts.size() == 4) {
                // Триангуляция квадрата
                faceTriplets.push_back({verts[0], verts[1], verts[2]});
                faceTriplets.push_back({verts[0], verts[2], verts[3]});
            } else {
                // TODO - сделать универсальный триангулятор
                // С чем-то сложнее пока не работаем
                std::cerr << "OBJModel: face with " << verts.size() << " verts skipped\n";
            }
        } else if (token == "usemtl") {
            // Работаем с материалами
            std::string mtlName;
            if (iss >> mtlName) {
                auto it = materialBindings.find(mtlName);
                currentMaterial = (it != materialBindings.end()) ? it->second : defaultMaterial.get();
            }
        }
    }

    // Создаём треугольники
    for (const auto &ft : faceTriplets) {
        if (
                ft.v1 < 1
             || ft.v1 > (int)positions.size()
             || ft.v2 < 1
             || ft.v2 > (int)positions.size()
             || ft.v3 < 1 ||
             ft.v3 > (int)positions.size()
        ) {
            std::cerr << "OBJModel: invalid vertex index, skipping face\n";
            continue;
        }
        triangles.emplace_back(positions[ft.v1-1], positions[ft.v2-1], positions[ft.v3-1], currentMaterial);
    }

    // Заполняем shapes указателями на наши треугольнички
    shapes.clear();
    shapes.reserve(triangles.size());
    for (const auto& tri : triangles) {
        shapes.push_back(&tri);
    }
    buildBVH();
}
