//
// Created by iliya on 5/2/26.
//

#include "tracer/geometry.h"
#include "tracer/textures.h"
#include "obj_model.h"
#include <fstream>
#include <sstream>
#include <iostream>

OBJModel::OBJModel(const std::string &file, const Vector3d& zero, const Float3 &rot, float scale)
        : filename(file), scale(scale), zero(zero),
          rotation(eulerRotate(rot.x, rot.y, rot.z)) {}

void OBJModel::bindMaterial(const std::string &name, const IMaterial *mat) {
    materialBindings[name] = mat;
}

void OBJModel::load() {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "OBJModel: cannot open " << filename << std::endl;
        return;
    }

    // Держим и позиции и текстурные координаты
    std::vector<Vector3d> positions;
    std::vector<Float2> texCoords;
    std::string line;

    ITexture *defaultTex = new PlainTexture(Float3{.5f, .0f, .5f});
    IMaterial *defaultMaterial = new Lambertian(defaultTex);

    const IMaterial *currentMaterial = defaultMaterial;

    struct Triplet { int v, vt, vn; };
    struct Face {Triplet a, b, c; const IMaterial* mat; };
    std::vector<Face> faces;

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
        }
        else if (token == "vt") {
            float u, v;
            if (iss >> u >> v)
                texCoords.push_back({u, v});
        }
        else if (token == "f") {
            // Если добавляется некоторая поверхность
            std::vector<std::string> verts;
            std::string vtx;
            while (iss >> vtx) verts.push_back(vtx);

            if (verts.size() == 3 || verts.size() == 4) {
                // Если у нас треугольник или четырёхугольник
                auto parseVertex = [&](const std::string& str, Triplet& t) {
                    std::istringstream vss(str);
                    std::string part;
                    std::getline(vss, part, '/'); t.v = std::stoi(part);
                    std::getline(vss, part, '/'); t.vt = part.empty() ? 0 : std::stoi(part);
                    std::getline(vss, part, '/'); t.vn = part.empty() ? 0 : std::stoi(part);
                };

                Triplet t1, t2, t3;
                parseVertex(verts[0], t1);
                parseVertex(verts[1], t2);
                parseVertex(verts[2], t3);
                faces.push_back({t1, t2, t3, currentMaterial});

                if (verts.size() == 4) {
                    Triplet t4;
                    parseVertex(verts[3], t4);
                    faces.push_back({t1, t3, t4, currentMaterial});
                }
            } else {
                // Другие игнорируем
                std::cerr << "OBJModel: face with " << verts.size() << " verts skipped\n";
            }
        }
        else if (token == "usemtl") {
            // Меняем материал
            std::string mtlName;
            if (iss >> mtlName) {
                auto it = materialBindings.find(mtlName);
                currentMaterial = (it != materialBindings.end()) ? it->second : defaultMaterial;
            }
        }
    }
    // Создаём треугольники из индексов вершин
    for (const auto &i: faces) {
        const Triplet &a = i.a;
        const Triplet &b = i.b;
        const Triplet &c = i.c;

        if (a.v < 1 || a.v > (int)positions.size() ||
                                  b.v < 1 || b.v > (int)positions.size() ||
                                                        c.v < 1 || c.v > (int)positions.size()) {
            std::cerr << "OBJModel: invalid vertex index, skipping face\n";
            continue;
        }

        bool hasUV = (a.vt > 0 && b.vt > 0 && c.vt > 0) &&
                     (a.vt <= (int)texCoords.size() &&
                      b.vt <= (int)texCoords.size() &&
                      c.vt <= (int)texCoords.size());

        if (hasUV) {
            triangles.emplace_back(
                    positions[a.v-1], positions[b.v-1], positions[c.v-1],
                    texCoords[a.vt-1], texCoords[b.vt-1], texCoords[c.vt-1],
                    i.mat);
        } else {
            triangles.emplace_back(
                    positions[a.v-1], positions[b.v-1], positions[c.v-1],
                    i.mat);
        }
    }

    shapes.clear();
    shapes.reserve(triangles.size());
    for (const auto& tri : triangles) shapes.push_back(&tri);
    buildBVH();
}
