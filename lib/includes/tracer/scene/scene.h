//
// Created by iliya on 4/19/26.
//

#include "tracer/interfaces.h"
#include "tracer/geometry.h"
#include <vector>
#include <memory>

#ifndef TRACER_SCENE_SCENE_H
#define TRACER_SCENE_SCENE_H


class Scene {
private:
    std::vector<std::shared_ptr<IShape>> shapes;
    std::vector<std::shared_ptr<ILight>> lights;
public:
    const std::vector<std::shared_ptr<IShape>> &getShapes() const;
    const std::vector<std::shared_ptr<ILight>> &getLights() const;

    void add(std::shared_ptr<IShape> shape);
    void add(std::shared_ptr<ILight> light);

    bool intersect(const Ray& ray, float t_min, float t_max, HitRecord& rec) const;
};


#endif // TRACER_SCENE_SCENE_H
