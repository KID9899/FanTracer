//
// Created by iliya on 4/27/26.
//

#include "tracer/c_api/interfaces.h"
#include "tracer/c_api/core.h"
#include "tracer/c_api/structs.h"
#include "scene.h"

#ifndef CAPI_TRACER_SCENE_CAMERA_H
#define CAPI_TRACER_SCENE_CAMERA_H
EXTERN_PREFIX

make_capi(Camera);

ccls(Camera) Camera_make(const ccls(Vector3d) origin, const ccls(Vector3d) view, float horizontal, float vertical, float angle);
void Camera_destroy(ccls(Camera) self);

ccls(Ray) Camera_getRay(const ccls(Camera) self, float u, float v);
bool Camera_render(const ccls(Camera) self, const ccls(Scene) scene, int width, int height, const char *filename, int samples_per_pixel, bool debug);

EXTERN_POSTFIX
#endif // CAPI_TRACER_SCENE_CAMERA_H
