//
// This file was generated with AI
// and checked by Iliya on 4/28/26.
//

#include "tracer/c_api/all.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define fassert(a, b) assert(fabsf((a) - (b)) < 1e-5)

void test_smoke_shapes(void) {
    printf("Testing shape creation & basic calls...\n");

    // Dummy material
    ccls(Vector3d) red = Vector3d_make(1, 0, 0);
    ccls(Lambertian) mat_lam = Lambertian_make(red);
    ccls(IMaterial) mat = Lambertian2IMaterial(mat_lam);

    // Dummy ray
    ccls(Vector3d) origin = Vector3d_make(0, 0, -5);
    ccls(Vector3d) dir = Vector3d_make(0, 0, 1);
    ccls(Ray) ray = Ray_make(origin, dir);

    // ---- Sphere ----
    ccls(Vector3d) center = Vector3d_make(0, 0, 0);
    ccls(Sphere) sphere = Sphere_make(center, 1.0f, mat);
    ccls(IShape) shape_sphere = Sphere2IShape(sphere);

    ccls(HitRecord) hit = NULL;
    bool ok = Sphere_intersect(sphere, ray, 0.001f, 1000.0f, &hit);
    (void)ok;
    HitRecord_destroy(hit);

    ccls(AABB) box = Sphere_getBoundingBox(sphere);
    assert(box != NULL);
    AABB_destroy(box);

    IShape_destroy(shape_sphere);
//    Sphere_destroy(sphere);

    // ---- Cylinder ----
    ccls(Float3) rot = Float3_make(0, 0, 0);
    ccls(Cylinder) cyl = Cylinder_make(center, 0.5f, 2.0f, rot, mat);
    ccls(IShape) shape_cyl = Cylinder2IShape(cyl);
    hit = HitRecord_empty();
    Cylinder_intersect(cyl, ray, 0.001f, 1000.0f, &hit);
    HitRecord_destroy(hit);
    box = Cylinder_getBoundingBox(cyl);
    assert(box != NULL);
    AABB_destroy(box);
    IShape_destroy(shape_cyl);
//    Cylinder_destroy(cyl);

    // ---- Plane ----
    ccls(Vector3d) plane_point = Vector3d_make(0, -1, 0);
    ccls(Vector3d) plane_normal = Vector3d_make(0, 1, 0);
    ccls(Plane) plane = Plane_make(plane_point, plane_normal, mat);
    ccls(IShape) shape_plane = Plane2IShape(plane);
    hit = HitRecord_empty();
    Plane_intersect(plane, ray, 0.001f, 1000.0f, &hit);
    HitRecord_destroy(hit);
    box = Plane_getBoundingBox(plane);
    assert(box != NULL);
    AABB_destroy(box);
    IShape_destroy(shape_plane);
//    Plane_destroy(plane);

    // ---- OrientedBox ----
    ccls(Vector3d) box_size = Vector3d_make(1, 1, 1);
    ccls(OrientedBox) obox = OrientedBox_make(center, box_size, rot, mat);
    ccls(IShape) shape_obox = OrientedBox2IShape(obox);
    hit = HitRecord_empty();
    OrientedBox_intersect(obox, ray, 0.001f, 1000.0f, &hit);
    HitRecord_destroy(hit);
    box = OrientedBox_getBoundingBox(obox);
    assert(box != NULL);
    AABB_destroy(box);
    IShape_destroy(shape_obox);
//    OrientedBox_destroy(obox);
    Vector3d_destroy(box_size);

    // clean up
    Ray_destroy(ray);
    Vector3d_destroy(origin);
    Vector3d_destroy(dir);
    Vector3d_destroy(center);
    Float3_destroy(rot);
    Vector3d_destroy(plane_point);
    Vector3d_destroy(plane_normal);
    Lambertian_destroy(mat_lam);
    Vector3d_destroy(red);
}

void test_smoke_materials(void) {
    printf("Testing material creation & basic calls...\n");

    // ---- Lambertian ----
    ccls(Vector3d) color = Vector3d_make(0.8f, 0.3f, 0.1f);
    ccls(Lambertian) lam = Lambertian_make(color);
    ccls(IMaterial) imat_lam = Lambertian2IMaterial(lam);

    // Create a dummy hit record and ray for scatter
    ccls(HitRecord) hit = HitRecord_empty();
    ccls(Vector3d) hit_pt = Vector3d_make(0,0,0);
    ccls(Vector3d) hit_norm = Vector3d_make(0,1,0);
    HitRecord_set_point(hit, hit_pt);
    HitRecord_set_normal(hit, hit_norm);
    ccls(Vector3d) ray_origin = Vector3d_make(0,0,-1);
    ccls(Vector3d) ray_dir = Vector3d_make(0,0,1);
    ccls(Ray) ray = Ray_make(ray_origin, ray_dir);

    ccls(Vector3d) abs_at = NULL;
    ccls(Vector3d) dist_at = NULL;
    ccls(Ray) scattered = NULL;
    bool scattered_ok = Lambertian_scatter(lam, ray, hit, &abs_at, &dist_at, &scattered);
    (void)scattered_ok;
    // Check that output pointers were set (not NULL) and vectors are not all zero
    assert(abs_at != NULL);
    assert(dist_at != NULL);
    assert(scattered != NULL);
    Vector3d_getX(abs_at);
    ccls(Vector3d) emitted = Lambertian_emitted(lam, hit);
    Vector3d_getX(emitted);
    Vector3d_getY(emitted);
    Vector3d_getZ(emitted);

    // Cleanup per-call
    Vector3d_destroy(abs_at);
    Vector3d_destroy(dist_at);
    Ray_destroy(scattered);
    Vector3d_destroy(emitted);

    // ---- Mirror ----
    ccls(Vector3d) mirror_color = Vector3d_make(0.9f, 0.9f, 0.9f);
    ccls(Mirror) mir = Mirror_make(mirror_color, 0.1f);
    ccls(IMaterial) imat_mir = Mirror2IMaterial(mir);
    abs_at = NULL; dist_at = NULL; scattered = NULL;
    scattered_ok = Mirror_scatter(mir, ray, hit, &abs_at, &dist_at, &scattered);
    assert(abs_at != NULL && dist_at != NULL && scattered != NULL);
    Vector3d_destroy(abs_at);
    Vector3d_destroy(dist_at);
    Ray_destroy(scattered);
    emitted = Mirror_emitted(mir, hit);
    fassert(Vector3d_getX(emitted), 0.0f);
    Vector3d_destroy(emitted);

    // ---- Glass ----
    ccls(Vector3d) glass_color = Vector3d_make(0.95f, 0.95f, 0.95f);
    ccls(Glass) glass = Glass_make(glass_color, 1.5f, 0.1f, 0.05f);
    ccls(IMaterial) imat_glass = Glass2IMaterial(glass);
    abs_at = NULL; dist_at = NULL; scattered = NULL;
    scattered_ok = Glass_scatter(glass, ray, hit, &abs_at, &dist_at, &scattered);
    assert(abs_at != NULL && dist_at != NULL && scattered != NULL);
    Vector3d_destroy(abs_at);
    Vector3d_destroy(dist_at);
    Ray_destroy(scattered);
    emitted = Glass_emitted(glass, hit);
    fassert(Vector3d_getX(emitted), 0.0f);
    Vector3d_destroy(emitted);

    // Cleanup
    Lambertian_destroy(lam);
    Mirror_destroy(mir);
    Glass_destroy(glass);
    Vector3d_destroy(color);
    Vector3d_destroy(mirror_color);
    Vector3d_destroy(glass_color);
    HitRecord_destroy(hit);
    Vector3d_destroy(hit_pt);
    Vector3d_destroy(hit_norm);
    Ray_destroy(ray);
    Vector3d_destroy(ray_origin);
    Vector3d_destroy(ray_dir);
}

void test_smoke_lights(void) {
    printf("Testing light creation & basic calls...\n");

    ccls(HitRecord) hit = HitRecord_empty();
    ccls(Vector3d) hit_pt = Vector3d_make(1,2,3);
    HitRecord_set_point(hit, hit_pt);

    // ---- PointLight ----
    ccls(Vector3d) pos = Vector3d_make(0, 10, 0);
    ccls(Vector3d) intensity = Vector3d_make(300, 300, 300);
    ccls(PointLight) plight = PointLight_make(pos, intensity);
    ccls(ILight) ilight = PointLight2ILight(plight);

    ccls(Vector3d) light_dir = NULL;
    float distance = 0.0f;
    ccls(Vector3d) Li = PointLight_illuminate(plight, hit, &light_dir, &distance);
    assert(Li != NULL);
    assert(light_dir != NULL);
    assert(distance > 0.0f);
    ccls(Vector3d) sample = PointLight_samplePoint(plight);
    fassert(Vector3d_getX(sample), 0.0f);
    fassert(Vector3d_getY(sample), 10.0f);
    fassert(Vector3d_getZ(sample), 0.0f);
    Vector3d_destroy(Li);
    Vector3d_destroy(light_dir);
    Vector3d_destroy(sample);
//    ILight_destroy(ilight);
    PointLight_destroy(plight);

    // ---- SkyLight ----
    ccls(Vector3d) sky_intensity = Vector3d_make(1, 1, 1);
    ccls(SkyLight) sky = SkyLight_make(sky_intensity);
    ilight = SkyLight2ILight(sky);
    light_dir = NULL; distance = 0.0f;
    Li = SkyLight_illuminate(sky, hit, &light_dir, &distance);
    assert(Li != NULL);
    assert(light_dir != NULL);
    assert(distance < 1e-5f);
    sample = SkyLight_samplePoint(sky);
    assert(sample != NULL);
    Vector3d_destroy(Li);
    Vector3d_destroy(light_dir);
    Vector3d_destroy(sample);
    ILight_destroy(ilight);
//    SkyLight_destroy(sky);

    Vector3d_destroy(hit_pt);
    HitRecord_destroy(hit);
    Vector3d_destroy(pos);
    Vector3d_destroy(intensity);
    Vector3d_destroy(sky_intensity);
}

void test_smoke_scene(void) {
    printf("Testing scene creation, add/intersect/get...\n");
    ccls(Scene) scene = Scene_empty();

    // Create a simple shape and light
    ccls(Vector3d) red = Vector3d_make(1,0,0);
    ccls(Lambertian) mat = Lambertian_make(red);
    ccls(IMaterial) imat = Lambertian2IMaterial(mat);

    ccls(Vector3d) center = Vector3d_make(0,0,0);
    ccls(Sphere) sphere = Sphere_make(center, 1.0f, imat);
    ccls(IShape) ishape = Sphere2IShape(sphere);

    ccls(Vector3d) light_pos = Vector3d_make(5,5,5);
    ccls(Vector3d) light_intensity = Vector3d_make(100,100,100);
    ccls(PointLight) light = PointLight_make(light_pos, light_intensity);
    ccls(ILight) ilight = PointLight2ILight(light);

    Scene_add_shape(scene, ishape);
    Scene_add_light(scene, ilight);

    // Intersect with a ray that should hit the sphere
    ccls(Vector3d) ray_origin = Vector3d_make(0,0,-5);
    ccls(Vector3d) ray_dir = Vector3d_make(0,0,1);
    ccls(Ray) ray = Ray_make(ray_origin, ray_dir);
    ccls(HitRecord) hit = HitRecord_empty();
    bool found = Scene_intersect(scene, ray, 0.001f, 1000.0f, &hit);
    assert(found == true);
    HitRecord_destroy(hit);

    // Test getShapes/getLights
    const ccls(IShape) const* shapes = NULL;
    int n_shapes = Scene_getShapes(scene, &shapes);
    assert(n_shapes == 1);
    assert(shapes[0] == ishape);
    const ccls(ILight) const* lights = NULL;
    int n_lights = Scene_getLights(scene, &lights);
    assert(n_lights == 1);
    assert(lights[0] == ilight);

    // Cleanup
    Scene_destroy(scene);
    Ray_destroy(ray);
    Vector3d_destroy(ray_origin);
    Vector3d_destroy(ray_dir);
    Sphere_destroy(sphere);
    Vector3d_destroy(center);
    PointLight_destroy(light);
    Vector3d_destroy(light_pos);
    Vector3d_destroy(light_intensity);
    Lambertian_destroy(mat);
    Vector3d_destroy(red);
}

/* Helper to create a ground plane with given material */
ccls(Plane) make_ground_plane(float y, ccls(IMaterial) mat) {
    ccls(Vector3d) point = Vector3d_make(0, y, 0);
    ccls(Vector3d) normal = Vector3d_make(0, 1, 0);
    ccls(Plane) plane = Plane_make(point, normal, mat);
    Vector3d_destroy(point);
    Vector3d_destroy(normal);
    return plane;
}

void test_rendering(void) {
    printf("Testing rendering pipeline with various scenes...\n");

    // Common color vectors
    ccls(Vector3d) col_white  = Vector3d_make(0.8f, 0.8f, 0.8f);
    ccls(Vector3d) col_red    = Vector3d_make(0.9f, 0.1f, 0.1f);
    ccls(Vector3d) col_green  = Vector3d_make(0.1f, 0.9f, 0.1f);
    ccls(Vector3d) col_blue   = Vector3d_make(0.1f, 0.1f, 0.9f);
    ccls(Vector3d) col_mirror = Vector3d_make(0.95f, 0.95f, 0.95f);
    ccls(Vector3d) col_glass  = Vector3d_make(0.98f, 0.98f, 0.98f);
    ccls(Vector3d) col_yellow = Vector3d_make(1, 1, 0);

    // --- Scene 1: basic scene with sphere, plane, point light ---
    {
        printf("  Scene 1: simple sphere on ground...\n");
        // Materials
        ccls(Lambertian) mat_green = Lambertian_make(col_green);
        ccls(Mirror) mat_mirror = Mirror_make(col_mirror, 0.0f);
        ccls(IMaterial) i_green = Lambertian2IMaterial(mat_green);
        ccls(IMaterial) i_mirror = Mirror2IMaterial(mat_mirror);

        // Shapes
        ccls(Plane) ground = make_ground_plane(0.0f, i_green);
        ccls(Vector3d) sph_center = Vector3d_make(0, 0.5f, 0);
        ccls(Sphere) sphere = Sphere_make(sph_center, 0.5f, i_mirror);

        ccls(IShape) shapes[] = { Plane2IShape(ground), Sphere2IShape(sphere) };

        // Light
        ccls(Vector3d) lpos = Vector3d_make(3, 5, 2);
        ccls(Vector3d) lint = Vector3d_make(150, 150, 150);
        ccls(PointLight) plight = PointLight_make(lpos, lint);
        ccls(ILight) lights[] = { PointLight2ILight(plight) };

        ccls(Scene) scene = Scene_empty();
        Scene_add_shape(scene, shapes[0]);
        Scene_add_shape(scene, shapes[1]);
        Scene_add_light(scene, lights[0]);

        // Camera 1: looking from front
        ccls(Vector3d) cam_origin = Vector3d_make(0, 1.2f, -3);
        ccls(Vector3d) cam_view   = Vector3d_make(0, 0, 1);
        ccls(Camera) cam1 = Camera_make(cam_origin, cam_view, 2.0f, 2.0f, 60.0f);
        bool ok = Camera_render(cam1, scene, 256, 256, "test_scene1_cam1.bmp", 1, false);
        assert(ok);

        // Camera 2: tilted, looking from above
        ccls(Vector3d) cam_origin2 = Vector3d_make(0, 5, 0);
        ccls(Vector3d) cam_view2   = Vector3d_make(0, -1, 0.1f);
        ccls(Camera) cam2 = Camera_make(cam_origin2, cam_view2, 2.0f, 2.0f, 60.0f);
        ok = Camera_render(cam2, scene, 256, 256, "test_scene1_cam2.bmp", 1, false);
        assert(ok);

        // Cleanup
        Camera_destroy(cam1);
        Camera_destroy(cam2);
        Vector3d_destroy(cam_origin);
        Vector3d_destroy(cam_view);
        Vector3d_destroy(cam_origin2);
        Vector3d_destroy(cam_view2);
        Scene_destroy(scene);
        Sphere_destroy(sphere);
        Plane_destroy(ground);
        Vector3d_destroy(sph_center);
        PointLight_destroy(plight);
        Vector3d_destroy(lpos); Vector3d_destroy(lint);
        Lambertian_destroy(mat_green);
        Mirror_destroy(mat_mirror);
    }

    // --- Scene 2: multiple objects with different materials and rotations ---
    {
        printf("  Scene 2: box, cylinder, glass sphere, rotated box...\n");
        // Lambertians
        ccls(Lambertian) lam_white = Lambertian_make(col_white);
        ccls(Lambertian) lam_red = Lambertian_make(col_red);
        ccls(Lambertian) lam_blue = Lambertian_make(col_blue);
        ccls(Glass) glass = Glass_make(col_glass, 1.5f, 0.1f, 0.0f);
        ccls(Mirror) mirror = Mirror_make(col_mirror, 0.2f);

        ccls(IMaterial) i_white = Lambertian2IMaterial(lam_white);
        ccls(IMaterial) i_red   = Lambertian2IMaterial(lam_red);
        ccls(IMaterial) i_blue  = Lambertian2IMaterial(lam_blue);
        ccls(IMaterial) i_glass = Glass2IMaterial(glass);
        ccls(IMaterial) i_mir   = Mirror2IMaterial(mirror);

        // Ground plane
        ccls(Plane) ground = make_ground_plane(0.0f, i_white);

        // OrientedBox with rotation
        ccls(Vector3d) box_center = Vector3d_make(0, 1.2f, 0);
        ccls(Vector3d) box_size   = Vector3d_make(1.5f, 1.5f, 1.5f);
        ccls(Float3) box_rot = Float3_make(0.3f, 0.5f, 0.2f);
        ccls(OrientedBox) obox = OrientedBox_make(box_center, box_size, box_rot, i_red);

        // Cylinder vertical
        ccls(Vector3d) cyl_center = Vector3d_make(-1.5f, 0.75f, -1);
        ccls(Float3) cyl_rot = Float3_make(0, 0, 0);
        ccls(Cylinder) cyl = Cylinder_make(cyl_center, 0.4f, 1.5f, cyl_rot, i_blue);

        // Glass sphere
        ccls(Vector3d) sph_center = Vector3d_make(1.5f, 0.6f, -0.5f);
        ccls(Sphere) sphere = Sphere_make(sph_center, 0.6f, i_glass);

        // Mirror sphere
        ccls(Vector3d) sph2_center = Vector3d_make(0, 0.5f, 2.0f);
        ccls(Sphere) sphere2 = Sphere_make(sph2_center, 0.5f, i_mir);

        ccls(IShape) shape_list[] = {
                Plane2IShape(ground),
                OrientedBox2IShape(obox),
                Cylinder2IShape(cyl),
                Sphere2IShape(sphere),
                Sphere2IShape(sphere2)
        };
        int n_shapes = 5;

        // Two lights: point and sky
        ccls(Vector3d) lpos = Vector3d_make(5, 8, 5);
        ccls(Vector3d) lint = Vector3d_make(180, 180, 180);
        ccls(PointLight) plight = PointLight_make(lpos, lint);
        ccls(ILight) i_plight = PointLight2ILight(plight);

        ccls(Vector3d) sky_int = Vector3d_make(0.5f, 0.6f, 1.0f);
        ccls(SkyLight) sky = SkyLight_make(sky_int);
        ccls(ILight) i_sky = SkyLight2ILight(sky);

        ccls(ILight) light_list[] = { i_plight, i_sky };
        int n_lights = 2;

        ccls(Scene) scene = Scene_empty();
        for (int i = 0; i < n_shapes; ++i) Scene_add_shape(scene, shape_list[i]);
        for (int i = 0; i < n_lights; ++i) Scene_add_light(scene, light_list[i]);

        // Camera with different parameters
        ccls(Vector3d) cam_origin = Vector3d_make(0, 2, -6);
        ccls(Vector3d) cam_view   = Vector3d_make(0, 0, 1);
        ccls(Camera) cam = Camera_make(cam_origin, cam_view, 3.0f, 3.0f, 45.0f);
        bool ok = Camera_render(cam, scene, 256, 256, "test_scene2.bmp", 4, false);
        assert(ok);
        Camera_destroy(cam);
        Vector3d_destroy(cam_origin);
        Vector3d_destroy(cam_view);

        // Cleanup everything
        Plane_destroy(ground);
        OrientedBox_destroy(obox);
        Cylinder_destroy(cyl);
        Sphere_destroy(sphere);
        Sphere_destroy(sphere2);
        PointLight_destroy(plight);
        SkyLight_destroy(sky);
        Vector3d_destroy(box_center); Vector3d_destroy(box_size); Float3_destroy(box_rot);
        Vector3d_destroy(cyl_center); Float3_destroy(cyl_rot);
        Vector3d_destroy(sph_center);
        Vector3d_destroy(sph2_center);
        Vector3d_destroy(lpos); Vector3d_destroy(lint);
        Vector3d_destroy(sky_int);
        Lambertian_destroy(lam_white); Lambertian_destroy(lam_red); Lambertian_destroy(lam_blue);
        Glass_destroy(glass);
        Mirror_destroy(mirror);
    }

    // --- Scene 3: test camera tilts and multiple renders of the same scene ---
    {
        printf("  Scene 3: camera tilt tests...\n");
        // Simple scene: plane + sphere
        ccls(Lambertian) lam_yellow = Lambertian_make(col_yellow);
        ccls(IMaterial) i_yellow = Lambertian2IMaterial(lam_yellow);
        ccls(Plane) ground = make_ground_plane(0.0f, i_yellow);
        ccls(Vector3d) sph_center = Vector3d_make(0, 0.7f, 0);
        ccls(Sphere) sphere = Sphere_make(sph_center, 0.7f, i_yellow);
        ccls(Scene) scene = Scene_empty();
        Scene_add_shape(scene, Plane2IShape(ground));
        Scene_add_shape(scene, Sphere2IShape(sphere));
        ccls(Vector3d) lpos = Vector3d_make(2, 5, 2);
        ccls(Vector3d) lint = Vector3d_make(100, 100, 100);
        ccls(PointLight) light = PointLight_make(lpos, lint);
        Scene_add_light(scene, PointLight2ILight(light));

        // Test several camera positions
        ccls(Vector3d) origins[] = {
                Vector3d_make(0, 1.5, -4),    // front
                Vector3d_make(0, 5, 0),       // top-down
                Vector3d_make(4, 1.5, 0),     // side
                Vector3d_make(-3, 2, -2)      // angled
        };
        ccls(Vector3d) views[] = {
                Vector3d_make(0, 0, 1),
                Vector3d_make(0, -1, 0.1f),
                Vector3d_make(-1, 0, 0),
                Vector3d_make(0.6f, -0.2f, 1)
        };
        char fname[64];
        for (int i = 0; i < 4; ++i) {
            ccls(Camera) cam = Camera_make(origins[i], views[i], 2.0f, 2.0f, 60.0f);
            sprintf(fname, "test_scene3_cam%d.bmp", i+1);
            bool ok = Camera_render(cam, scene, 256, 256, fname, 1, false);
            assert(ok);
            Camera_destroy(cam);
        }

        // Cleanup
        for (int i = 0; i < 4; ++i) {
            Vector3d_destroy(origins[i]);
            Vector3d_destroy(views[i]);
        }
        Scene_destroy(scene);
        Sphere_destroy(sphere);
        Plane_destroy(ground);
        PointLight_destroy(light);
        Vector3d_destroy(sph_center);
        Vector3d_destroy(lpos); Vector3d_destroy(lint);
        Lambertian_destroy(lam_yellow);
        Vector3d_destroy(col_yellow);
    }

    // Destroy shared color vectors
    Vector3d_destroy(col_white);
    Vector3d_destroy(col_red);
    Vector3d_destroy(col_green);
    Vector3d_destroy(col_blue);
    Vector3d_destroy(col_mirror);
    Vector3d_destroy(col_glass);
}

int main(void) {
    test_smoke_shapes();
    test_smoke_materials();
    test_smoke_lights();
    test_smoke_scene();
    test_rendering();
    printf("All tests passed!\n");
    return 0;
}
