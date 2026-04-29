//
// Created by iliya on 4/27/26.
//

#include <iostream>
#include "tracer/all.h"
#include "scene.h"

ccls(Scene) Scene_empty() {
    return _toc(Scene, new Scene);
}
void Scene_destroy(ccls(Scene) self) {
    delete _tocpp(Scene, self);
}

int Scene_getShapes(const ccls(Scene) self, const ccls(IShape) const **out) {
    auto &shapes = _tocppc(Scene, self)->getShapes();
    *out = reinterpret_cast<const ccls(IShape) const*>(shapes.data());
    return shapes.size();
}
int Scene_getLights(const ccls(Scene) self, const ccls(ILight) const **out) {
    auto &lights = _tocppc(Scene, self)->getLights();
    *out = reinterpret_cast<const ccls(ILight) const*>(lights.data());
    return lights.size();
}

void Scene_add_shape(ccls(Scene) self, const ccls(IShape) shape) {
    _tocpp(Scene, self)->add(_tocppc(IShape, shape));
}
void Scene_add_light(ccls(Scene) self, const ccls(ILight) light) {
    _tocpp(Scene, self)->add(_tocppc(ILight, light));
}

bool Scene_intersect(const ccls(Scene) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord) *hit) {
    HitRecord h;
    bool res = _tocppc(Scene, self)->intersect(_tocppci(Ray, ray), t_min, t_max, h);
    *hit = _rvtoc(HitRecord, h);
    return res;
}
