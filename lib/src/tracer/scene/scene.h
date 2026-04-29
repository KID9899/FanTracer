//
// Created by iliya on 4/19/26.
//

#include <vector>
#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_SCENE_SCENE_H
#define TRACER_SCENE_SCENE_H

// TODO - написать документацию
class Scene {
private:
    std::vector<const IShape*> shapes;
    std::vector<const ILight*> lights;
public:
    const std::vector<const IShape*> &getShapes() const noexcept;
    const std::vector<const ILight*> &getLights() const noexcept;

    void add(const IShape* shape) noexcept;
    void add(const ILight* light) noexcept;

    bool intersect(const Ray &ray, float t_min, float t_max, HitRecord &hit) const noexcept;
};


#endif // TRACER_SCENE_SCENE_H
