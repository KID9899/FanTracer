//
// Created by iliya on 4/17/26.
//

#include "tracer/c_api/all.h"
#include "tracer/all.h"

int main() {
    ccls(Scene) scene = Scene_empty();

    // === Материалы ===
    ccls(IMaterial) red    = Lambertian2IMaterial(Lambertian_make(Vector3d_make(0.8f, 0.2f, 0.2f)));
    ccls(IMaterial) mirror = Mirror2IMaterial(Mirror_make(Vector3d_make(0.95f, 0.95f, 0.95f), 0.0f));
    ccls(IMaterial) blue_g = Glass2IMaterial(Glass_make(Vector3d_make(0.5f, 0.5f, 0.8f), 1.01f, 0.5f, 0.6f));
    ccls(IMaterial) dark_g = Glass2IMaterial(Glass_make(Vector3d_make(0.5f, 0.5f, 0.5f), 1.52f, 0.2f, 0.2f));
    ccls(IMaterial) gray   = Lambertian2IMaterial(Lambertian_make(Vector3d_make(0.2f, 0.2f, 0.2f)));
    ccls(IMaterial) green  = Lambertian2IMaterial(Lambertian_make(Vector3d_make(0.2f, 0.8f, 0.2f)));

    // Пол
    Scene_add_shape(scene, Plane2IShape(Plane_make(Vector3d_make(0.f,0.f,0.f), Vector3d_make(0.f,1.f,0.f), gray)));

    // Объекты
//    Scene_add_shape(scene, OrientedBox2IShape(OrientedBox_make(Vector3d_make(0.0f,4.33f,-2.0f), Vector3d_make(5.f,5.f,5.f), Float3_make(.78f, .0f, .78f), mirror)));
//    Scene_add_shape(scene, Sphere2IShape(Sphere_make(Vector3d_make(11.f,8.f,-7.f), 8.f, mirror)));
//    Scene_add_shape(scene, Sphere2IShape(Sphere_make(Vector3d_make(3.5f,0.5f,-1.f), .5f, red)));
//    Scene_add_shape(scene, Cylinder2IShape(Cylinder_make(Vector3d_make(1.f,1.f,1.f), .5f, 3.f, Float3_make(0.3f, -2.3f, 0.f), green)));
//    Scene_add_shape(scene, OrientedBox2IShape(OrientedBox_make(Vector3d_make(1.4f,0.4f,11.f), Vector3d_make(2.7f,0.8f,2.f), Float3_make(.0f, .4f, .0f), blue_g)));
//    Scene_add_shape(scene, Sphere2IShape(Sphere_make(Vector3d_make(3.f,0.5f,13.f), .5f, dark_g)));

    OBJModel boy("cat.obj", {0.f, 0.f, 3.f}, {0.f, 0.f, 0.f}, .01f);
    boy.bindMaterial("Mat", new Lambertian(Vector3d(0.f,0.75f,1.0f)));
    boy.load();

    OBJModel girl("cat.obj", {6.f, 0.f, 3.f}, {0.f, 3.14f, 0.f}, .01f);
    girl.bindMaterial("Mat", new Lambertian(Vector3d(1.0f,0.75f,0.8f)));
    girl.load();

    Scene_add_shape(scene, _toc(IShape, dynamic_cast<IShape*>(&boy)));
    Scene_add_shape(scene, _toc(IShape, dynamic_cast<IShape*>(&girl)));

    _tocpp(Scene, scene)->buildBVH();

    // Свет
    Scene_add_light(scene, PointLight2ILight(PointLight_make(Vector3d_make(10.f, 10.f, 6.f), Vector3d_make(100.f, 100.f, 100.f))));
    Scene_add_light(scene, SkyLight2ILight(SkyLight_make(Vector3d_make(.2f, .2f, .2f))));

    // Камера
    ccls(Camera) cam = Camera_make(Vector3d_make(15.f, 1.f, 15.f), Vector3d_make(-1.f, 0.f, -1.0f), .5f, .5f, 0.f);

    Camera_render(cam, scene, 1024, 1024, "output.ppm", 100, true);
    return 0;
}
