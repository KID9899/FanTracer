//
// Created by iliya on 4/19/26.
//

#include <vector>
#include "tracer/interfaces.h"
#include "tracer/core.h"
#include "tracer/structs.h"

#ifndef TRACER_SCENE_SCENE_H
#define TRACER_SCENE_SCENE_H

class Scene: public IShapesGroup {
private:
    std::vector<const ILight*> lights;
public:
    using IShapesGroup::add;
    inline void add(const ILight* light) noexcept {
        lights.push_back(light);
    }
    inline const std::vector<const ILight*>& getLights() const noexcept {
        return lights;
    }
};

#endif // TRACER_SCENE_SCENE_H
