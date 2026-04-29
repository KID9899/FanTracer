//
// Created by iliya on 4/27/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"

#ifndef CAPI_TRACER_SCENE_SCENE_H
#define CAPI_TRACER_SCENE_SCENE_H
EXTERN_PREFIX

make_capi(Scene);

ccls(Scene) Scene_empty();
void Scene_destroy(ccls(Scene) self);

int Scene_getShapes(const ccls(Scene) self, const ccls(IShape)const **out);
int Scene_getLights(const ccls(Scene) self, const ccls(ILight)const **out);

void Scene_add_shape(ccls(Scene) self, const ccls(IShape) shape);
void Scene_add_light(ccls(Scene) self, const ccls(ILight) light);

bool Scene_intersect(const ccls(Scene) self, const ccls(Ray) ray, float t_min, float t_max, ccls(HitRecord) *hit);

EXTERN_POSTFIX
#endif // CAPI_TRACER_SCENE_SCENE_H
