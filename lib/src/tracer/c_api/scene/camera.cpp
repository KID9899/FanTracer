//
// Created by iliya on 4/27/26.
//

#include <string>
#include "tracer/all.h"
#include "camera.h"

ccls(Camera) Camera_make(const ccls(Vector3d) origin, const ccls(Vector3d) view, float horizontal, float vertical, float angle) {
    return _toc(Camera, new Camera(_tocppci(Vector3d, origin), _tocppci(Vector3d, view), horizontal, vertical, angle));
}
void Camera_destroy(ccls(Camera) self) {
    delete _tocpp(Camera, self);
}

ccls(Ray) Camera_getRay(const ccls(Camera) self, float u, float v) {
    return _rvtoc(Ray, _tocppc(Camera, self)->getRay(u, v));
}

bool Camera_render(const ccls(Camera) self, const ccls(Scene) scene, int width, int height, const char *filename, int samples_per_pixel, bool debug) {
    return _tocppc(Camera, self)->render(_tocppci(Scene, scene), width, height, std::string(filename), samples_per_pixel, debug);
}
