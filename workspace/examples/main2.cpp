//
// Created by iliya on 4/17/26.
//

#include "tracer/all.h"

int main() {
    Scene scene;

    // === Материалы ===
    auto tex     = new PlainTexture(Float3{0.2, 0.2, 0.2});
    auto gradTex = new GradientTexture(Float3{1,0,0}, Float3{0,0,1});

    auto gray = new Lambertian(tex);
    auto gradMat = new Lambertian(gradTex);

    // Пол
    scene.add(new Plane(Float3{0.f,0.f,0.f}, Float3{0.f,1.f,0.f}, gray));

//    auto imgTex = new BMPTexture();
//    imgTex->load("Cat_diffuse.bmp");
//    Lambertian* imgMat = new Lambertian(imgTex);

//    OBJModel boy("cat2.obj", {6.f, 1.8f, 3.f}, {-1.52f, -1.52f, 0.f}, .1f);
//    boy.bindMaterial("Cat", imgMat);
//    boy.load();

//    OBJModel vvp("vvp.obj", {0.f, 2.f, 3.f}, {-1.52f, 1.f, 0.f}, .02f);
//    vvp.load();

//    OBJModel girl("cat.obj", {6.f, 0.f, 3.f}, {0.f, 3.14f, 0.f}, .01f);
//    girl.bindMaterial("Mat", new Lambertian(Vector3d(1.0f,0.75f,0.8f)));
//    girl.load();

//    scene.add(&boy);
//    scene.add(&vvp);

    OBJModel tower("objTower.obj", {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, .3f);

    auto germanyLINE = new BMPTexture();
    auto germany0WHITE = new BMPTexture();
    auto entr002M = new BMPTexture();
    auto clay07XL = new BMPTexture();
    auto egypt_011 = new BMPTexture();
    auto wndw107M = new BMPTexture();
    auto hungary009 = new BMPTexture();
    germanyLINE->load("germanyLINE.bmp");
    germany0WHITE->load("germany0WHITE.bmp");
    entr002M->load("entr002M.bmp");
    clay07XL->load("clay07XL.bmp");
    egypt_011->load("egypt_011.bmp");
    wndw107M->load("wndw107M.bmp");
    hungary009->load("hungary009.bmp");
    IMaterial* A2SG = new Mirror(germanyLINE, .05f, {.1f, .1f, .1f});
    IMaterial* lambert78SG = new Mirror(germany0WHITE, .05f, {.1f, .1f, .1f});
    IMaterial* lambert79SG = new Mirror(entr002M, .05f, {.1f, .1f, .1f});
    IMaterial* lambert80SG = new Mirror(clay07XL, .05f, {.1f, .1f, .1f});
    IMaterial* lambert81SG = new Mirror(egypt_011, .05f, {.1f, .1f, .1f});
    IMaterial* lambert82SG = new Mirror(wndw107M, .05f, {.1f, .1f, .1f});
    IMaterial* lambert92SG = new Mirror(hungary009, .05f, {.1f, .1f, .1f});
    tower.bindMaterial("A2SG", A2SG);
    tower.bindMaterial("lambert78SG", lambert78SG);
    tower.bindMaterial("lambert79SG", lambert79SG);
    tower.bindMaterial("lambert80SG", lambert80SG);
    tower.bindMaterial("lambert81SG", lambert81SG);
    tower.bindMaterial("lambert82SG", lambert82SG);
    tower.bindMaterial("lambert92SG", lambert92SG);

    tower.load();
    scene.add(&tower);

    scene.buildBVH();

    // Свет
    scene.add(new PointLight(Float3{10.f, 10.f, 6.f}, Float3{150.f, 150.f, 150.f}));
    scene.add(new SkyLight(Float3{.5f, .5f, .5f}));

    // Камера
    Camera cam(Float3{15.f, 3.f, 15.f}, Float3{-1.f, 0.f, -1.0f}, .5f, .5f, 0.f);

    cam.render(scene, 1024, 1024, "output.ppm", 100, true);
    return 0;
}
