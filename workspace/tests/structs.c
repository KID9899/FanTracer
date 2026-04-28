//
// This file was generated with AI
// and checked by Iliya on 4/28/26.
//

#include "tracer/c_api/all.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define fassert(a, b) assert(fabsf((a) - (b)) < 1e-5)

// ------------------------------------------------------------
// Ray tests
// ------------------------------------------------------------
void test_Ray(void) {
    // --- empty ---
    ccls(Ray) r_empty = Ray_empty();
    assert(r_empty != NULL);
    Ray_destroy(r_empty);

    // --- make, origin, direction ---
    ccls(Vector3d) org = Vector3d_make(1.0f, 2.0f, 3.0f);
    ccls(Vector3d) dir = Vector3d_make(4.0f, 5.0f, 6.0f);
    ccls(Ray) ray = Ray_make(org, dir);
    ccls(Vector3d) got_org = Ray_origin(ray);
    ccls(Vector3d) got_dir = Ray_direction(ray);

    fassert(Vector3d_getX(got_org), 1.0f);
    fassert(Vector3d_getY(got_org), 2.0f);
    fassert(Vector3d_getZ(got_org), 3.0f);
    fassert(Vector3d_getX(got_dir), 4.0f);
    fassert(Vector3d_getY(got_dir), 5.0f);
    fassert(Vector3d_getZ(got_dir), 6.0f);

    Vector3d_destroy(org);
    Vector3d_destroy(dir);

    // --- Ray_at ---
    ccls(Vector3d) p = Ray_at(ray, 2.0f);
    fassert(Vector3d_getX(p), 9.0f);
    fassert(Vector3d_getY(p), 12.0f);
    fassert(Vector3d_getZ(p), 15.0f);
    Vector3d_destroy(p);

    // --- copy ---
    ccls(Ray) ray_copy = Ray_copy(ray);
    ccls(Vector3d) copy_org = Ray_origin(ray_copy);
    fassert(Vector3d_getX(copy_org), 1.0f);
    Ray_destroy(ray_copy);
    Ray_destroy(ray);
}

// ------------------------------------------------------------
// HitRecord tests
// ------------------------------------------------------------
void test_HitRecord(void) {
    // --- empty ---
    ccls(HitRecord) rec = HitRecord_empty();
    fassert(HitRecord_get_t(rec), 0.0f);
    const ccls(Vector3d) pt = HitRecord_get_point(rec);
    fassert(Vector3d_getX(pt), 0.0f);
    fassert(Vector3d_getY(pt), 0.0f);
    fassert(Vector3d_getZ(pt), 0.0f);
    assert(HitRecord_get_frontFace(rec) == false);
    assert(HitRecord_get_material(rec) == NULL);

    // --- setters and getters ---
    HitRecord_set_t(rec, 2.5f);
    fassert(HitRecord_get_t(rec), 2.5f);

    ccls(Vector3d) new_point = Vector3d_make(7, 8, 9);
    HitRecord_set_point(rec, new_point);
    const ccls(Vector3d) pp = HitRecord_get_point(rec);
    fassert(Vector3d_getX(pp), 7.0f);
    fassert(Vector3d_getY(pp), 8.0f);
    fassert(Vector3d_getZ(pp), 9.0f);
    Vector3d_destroy(new_point);

    ccls(Vector3d) new_normal = Vector3d_make(0, 0, 1);
    HitRecord_set_normal(rec, new_normal);
    const ccls(Vector3d) pn = HitRecord_get_normal(rec);
    fassert(Vector3d_getZ(pn), 1.0f);
    Vector3d_destroy(new_normal);

    HitRecord_set_frontFace(rec, true);
    assert(HitRecord_get_frontFace(rec) == true);

    // Set material
    ccls(IMaterial) dummy_mat = (ccls(IMaterial))0xDEADBEEF;
    HitRecord_set_material(rec, dummy_mat);
    assert(HitRecord_get_material(rec) == dummy_mat);

    // --- copy ---
    ccls(HitRecord) copy = HitRecord_copy(rec);
    fassert(HitRecord_get_t(copy), 2.5f);
    assert(HitRecord_get_frontFace(copy) == true);
    assert(HitRecord_get_material(copy) == dummy_mat);
    const ccls(Vector3d) cp = HitRecord_get_point(copy);
    fassert(Vector3d_getX(cp), 7.0f);
    HitRecord_destroy(copy);

    HitRecord_destroy(rec);
}

// ------------------------------------------------------------
// AABB tests
// ------------------------------------------------------------
void test_AABB(void) {
    // --- empty ---
    ccls(AABB) box = AABB_empty();
    ccls(Vector3d) mn = AABB_min(box);
    ccls(Vector3d) mx = AABB_max(box);
    fassert(Vector3d_getX(mn), 0.0f);
    fassert(Vector3d_getY(mn), 0.0f);
    fassert(Vector3d_getZ(mn), 0.0f);
    fassert(Vector3d_getX(mx), 0.0f);
    AABB_destroy(box);

    // --- make, min, max ---
    ccls(Vector3d) vmin = Vector3d_make(-1.0f, -2.0f, -3.0f);
    ccls(Vector3d) vmax = Vector3d_make(1.0f, 2.0f, 3.0f);
    ccls(AABB) aabb = AABB_make(vmin, vmax);

    ccls(Vector3d) gmin = AABB_min(aabb);
    fassert(Vector3d_getX(gmin), -1.0f);
    fassert(Vector3d_getY(gmin), -2.0f);
    fassert(Vector3d_getZ(gmin), -3.0f);

    ccls(Vector3d) gmax = AABB_max(aabb);
    fassert(Vector3d_getX(gmax), 1.0f);

    // --- set_min / set_max ---
    ccls(Vector3d) new_min = Vector3d_make(-5.0f, -5.0f, -5.0f);
    AABB_set_min(aabb, new_min);
    gmin = AABB_min(aabb);
    fassert(Vector3d_getX(gmin), -5.0f);
    Vector3d_destroy(new_min);

    ccls(Vector3d) new_max = Vector3d_make(5.0f, 5.0f, 5.0f);
    AABB_set_max(aabb, new_max);
    gmax = AABB_max(aabb);
    fassert(Vector3d_getX(gmax), 5.0f);
    Vector3d_destroy(new_max);

    Vector3d_destroy(vmin);
    Vector3d_destroy(vmax);

    // --- copy ---
    ccls(AABB) copy = AABB_copy(aabb);
    ccls(Vector3d) cmax = AABB_max(copy);
    fassert(Vector3d_getX(cmax), 5.0f);
    AABB_destroy(copy);
    AABB_destroy(aabb);
}

int main(void) {
    test_Ray();
    test_HitRecord();
    test_AABB();
    printf("All struct tests passed!\n");
    return 0;
}
