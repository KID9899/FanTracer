// main.c - Tests for tracer geometry functions
// Include the top-level API header
#include "tracer/c_api/core.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define fassert(a, b) assert(fabsf((a) - (b)) < 1e-5)

// ------------------------------------------------------------
// Float3 tests
// ------------------------------------------------------------
void test_Float3(void) {
    // Float3_make, getters, setters
    ccls(Float3) f = Float3_make(1.0f, 2.0f, 3.0f);
    fassert(Float3_x(f), 1.0f);
    fassert(Float3_y(f), 2.0f);
    fassert(Float3_z(f), 3.0f);

    Float3_set_x(f, 10.0f);
    fassert(Float3_x(f), 10.0f);
    Float3_set_y(f, 20.0f);
    fassert(Float3_y(f), 20.0f);
    Float3_set_z(f, 30.0f);
    fassert(Float3_z(f), 30.0f);

    Float3_destroy(f);

    // Float3_empty
    ccls(Float3) e = Float3_empty();
    fassert(Float3_x(e), 0.0f);
    fassert(Float3_y(e), 0.0f);
    fassert(Float3_z(e), 0.0f);
    Float3_destroy(e);
}

// ------------------------------------------------------------
// Vector3d tests
// ------------------------------------------------------------
void test_Vector3d(void) {
    // --- constructors ---
    ccls(Vector3d) v1 = Vector3d_make(1.0f, 2.0f, 3.0f);
    fassert(Vector3d_getX(v1), 1.0f);
    fassert(Vector3d_getY(v1), 2.0f);
    fassert(Vector3d_getZ(v1), 3.0f);

    ccls(Vector3d) vfill = Vector3d_fill(5.0f);
    fassert(Vector3d_getX(vfill), 5.0f);
    fassert(Vector3d_getY(vfill), 5.0f);
    fassert(Vector3d_getZ(vfill), 5.0f);
    Vector3d_destroy(vfill);

    ccls(Vector3d) vempty = Vector3d_empty();
    fassert(Vector3d_getX(vempty), 0.0f);
    fassert(Vector3d_getY(vempty), 0.0f);
    fassert(Vector3d_getZ(vempty), 0.0f);
    Vector3d_destroy(vempty);

    ccls(Vector3d) vcopy = Vector3d_copy(v1);
    fassert(Vector3d_getX(vcopy), 1.0f);
    fassert(Vector3d_getY(vcopy), 2.0f);
    fassert(Vector3d_getZ(vcopy), 3.0f);
    Vector3d_destroy(vcopy);

    // from_f3
    ccls(Float3) f3 = Float3_make(7.0f, 8.0f, 9.0f);
    ccls(Vector3d) vfromf3 = Vector3d_from_f3(f3);
    fassert(Vector3d_getX(vfromf3), 7.0f);
    fassert(Vector3d_getY(vfromf3), 8.0f);
    fassert(Vector3d_getZ(vfromf3), 9.0f);
    Float3_destroy(f3);
    Vector3d_destroy(vfromf3);

    // --- unsafeCreateFromXMM ---
    __m128 xmm = _mm_set_ps(0.f, 3.0f, 2.0f, 1.0f);
    ccls(Vector3d) usf = Vector3d_unsafeCreateFromXMM(xmm);
    fassert(Vector3d_getX(usf), 1.0f);
    fassert(Vector3d_getY(usf), 2.0f);
    fassert(Vector3d_getZ(usf), 3.0f);
    Vector3d_destroy(vfromf3);
    (void)xmm;

    // --- getData ---
    // Думаю, достаточно проверить, что он правильно вызывается
    __m128 data = Vector3d_getData(v1);
    (void)data;

    // --- replace ---
    ccls(Vector3d) vrepX = Vector3d_replaceX(v1, 10.0f);
    fassert(Vector3d_getX(vrepX), 10.0f);
    fassert(Vector3d_getY(vrepX), 2.0f);
    fassert(Vector3d_getZ(vrepX), 3.0f);
    Vector3d_destroy(vrepX);

    ccls(Vector3d) vrepY = Vector3d_replaceY(v1, 20.0f);
    fassert(Vector3d_getY(vrepY), 20.0f);
    Vector3d_destroy(vrepY);

    ccls(Vector3d) vrepZ = Vector3d_replaceZ(v1, 30.0f);
    fassert(Vector3d_getZ(vrepZ), 30.0f);
    Vector3d_destroy(vrepZ);

    // --- dot products ---
    ccls(Vector3d) a = Vector3d_make(1, 2, 3);
    ccls(Vector3d) b = Vector3d_make(4, 5, 6);
    float d = Vector3d_dot(a, b);
    fassert(d, 1*4 + 2*5 + 3*6);

    float dxy = Vector3d_dotXY(a, b);
    fassert(dxy, 1*4 + 2*5);
    float dxz = Vector3d_dotXZ(a, b);
    fassert(dxz, 1*4 + 3*6);
    float dyz = Vector3d_dotYZ(a, b);
    fassert(dyz, 2*5 + 3*6);
    Vector3d_destroy(a); Vector3d_destroy(b);

    // --- in-place arithmetic ---
    ccls(Vector3d) vself = Vector3d_make(1, 2, 3);
    ccls(Vector3d) vother = Vector3d_make(4, 5, 6);

    ccls(Vector3d) vret = Vector3d_add_assign(vself, vother);
    fassert(Vector3d_getX(vself), 5);
    fassert(Vector3d_getY(vself), 7);
    fassert(Vector3d_getZ(vself), 9);
    assert(vret == vself);
    if (vret != vself) {
        Vector3d_destroy(vret);
    }

    Vector3d_sub_assign(vself, vother);
    fassert(Vector3d_getX(vself), 1);
    fassert(Vector3d_getY(vself), 2);
    fassert(Vector3d_getZ(vself), 3);

    Vector3d_mul_assign(vself, vother);
    fassert(Vector3d_getX(vself), 4);
    fassert(Vector3d_getY(vself), 10);
    fassert(Vector3d_getZ(vself), 18);

    Vector3d_div_assign(vself, vother);
    fassert(Vector3d_getX(vself), 1);
    fassert(Vector3d_getY(vself), 2);
    fassert(Vector3d_getZ(vself), 3);

    Vector3d_smul_assign(vself, 2.0f);
    fassert(Vector3d_getX(vself), 2);
    fassert(Vector3d_getY(vself), 4);
    fassert(Vector3d_getZ(vself), 6);
    Vector3d_sdiv_assign(vself, 2.0f);
    fassert(Vector3d_getX(vself), 1);
    fassert(Vector3d_getY(vself), 2);
    fassert(Vector3d_getZ(vself), 3);

    ccls(Vector3d) neg = Vector3d_neg(vself);
    fassert(Vector3d_getX(neg), -1);
    fassert(Vector3d_getY(neg), -2);
    fassert(Vector3d_getZ(neg), -3);
    Vector3d_destroy(neg);

    ccls(Vector3d) vand = Vector3d_copy(vself);
    Vector3d_and_assign(vand, vand);
    fassert(Vector3d_getX(vand), 1);
    fassert(Vector3d_getY(vand), 2);
    fassert(Vector3d_getZ(vand), 3);
    Vector3d_or_assign(vand, vself);
    fassert(Vector3d_getX(vand), 1);
    fassert(Vector3d_getY(vand), 2);
    fassert(Vector3d_getZ(vand), 3);
    Vector3d_destroy(vand);

    Vector3d_destroy(vself); Vector3d_destroy(vother);

    // --- hypot, length ---
    vself = Vector3d_make(3, 4, 0);
    float h = Vector3d_hypot(vself);
    fassert(h, 25.0f);
    float len = Vector3d_length(vself);
    fassert(len, 5.0f);

    // --- max, min ---
    fassert(Vector3d_max(vself), 4.0f);
    fassert(Vector3d_min(vself), 0.0f);
    Vector3d_destroy(vself);

    // --- abs ---
    vself = Vector3d_make(-1, 2, -3);
    ccls(Vector3d) vabs = Vector3d_abs(vself);
    fassert(Vector3d_getX(vabs), 1);
    fassert(Vector3d_getY(vabs), 2);
    fassert(Vector3d_getZ(vabs), 3);
    Vector3d_destroy(vabs);

    // --- sign ---
    ccls(Vector3d) vsign = Vector3d_sign(vself);
    fassert(Vector3d_getX(vsign), -1.0f);
    fassert(Vector3d_getY(vsign), 1.0f);
    fassert(Vector3d_getZ(vsign), -1.0f);
    Vector3d_destroy(vsign);

    ccls(Vector3d) vszero = Vector3d_make(0.0f, -0.0f, 0.0f);
    ccls(Vector3d) sign_zero = Vector3d_sign(vszero);
    fassert(Vector3d_getX(sign_zero), 1.0f);
    fassert(Vector3d_getY(sign_zero), -1.0f);
    fassert(Vector3d_getZ(sign_zero), 1.0f);
    Vector3d_destroy(sign_zero);
    Vector3d_destroy(vszero);
    Vector3d_destroy(vself);

    // --- normalize ---
    vself = Vector3d_make(0, 3, 4);
    ccls(Vector3d) vnorm = Vector3d_normalize(vself);
    float nlen = Vector3d_length(vnorm);
    fassert(nlen, 1.0f);

    fassert(Vector3d_getX(vnorm), 0.0f);
    fassert(Vector3d_getY(vnorm), 0.6f);
    fassert(Vector3d_getZ(vnorm), 0.8f);
    Vector3d_destroy(vnorm);
    Vector3d_destroy(vself);

    // --- cross ---
    a = Vector3d_make(1, 0, 0);
    b = Vector3d_make(0, 1, 0);
    ccls(Vector3d) c = Vector3d_cross(a, b);
    fassert(Vector3d_getX(c), 0.f);
    fassert(Vector3d_getY(c), 0.f);
    fassert(Vector3d_getZ(c), 1.f);
    Vector3d_destroy(c); Vector3d_destroy(a); Vector3d_destroy(b);

    // --- non-assign arithmetic ---
    a = Vector3d_make(1, 2, 3);
    b = Vector3d_make(4, 5, 6);
    ccls(Vector3d) vadd = Vector3d_add(a, b);
    fassert(Vector3d_getX(vadd), 5);
    fassert(Vector3d_getY(vadd), 7);
    fassert(Vector3d_getZ(vadd), 9);
    Vector3d_destroy(vadd);
    ccls(Vector3d) vsub = Vector3d_sub(a, b);
    fassert(Vector3d_getX(vsub), -3);
    fassert(Vector3d_getY(vsub), -3);
    fassert(Vector3d_getZ(vsub), -3);
    Vector3d_destroy(vsub);
    ccls(Vector3d) vmul = Vector3d_mul(a, b);
    fassert(Vector3d_getX(vmul), 4);
    fassert(Vector3d_getY(vmul), 10);
    fassert(Vector3d_getZ(vmul), 18);
    Vector3d_destroy(vmul);
    ccls(Vector3d) vdiv = Vector3d_div(a, b);
    fassert(Vector3d_getX(vdiv), 0.25f);
    fassert(Vector3d_getY(vdiv), 0.4f);
    fassert(Vector3d_getZ(vdiv), 0.5f);
    Vector3d_destroy(vdiv);
    ccls(Vector3d) vsmul = Vector3d_smul(a, 2.0f);
    fassert(Vector3d_getX(vsmul), 2);
    fassert(Vector3d_getY(vsmul), 4);
    fassert(Vector3d_getZ(vsmul), 6);
    Vector3d_destroy(vsmul);
    ccls(Vector3d) vsdiv = Vector3d_sdiv(b, 2.0f);
    fassert(Vector3d_getX(vsdiv), 2);
    fassert(Vector3d_getY(vsdiv), 2.5f);
    fassert(Vector3d_getZ(vsdiv), 3);
    Vector3d_destroy(vsdiv);

    // and, or
    ccls(Vector3d) vand2 = Vector3d_and(a, a);
    fassert(Vector3d_getX(vand2), 1);
    Vector3d_destroy(vand2);

    Vector3d_destroy(a); Vector3d_destroy(b);

    // --- comparisons ---
    a = Vector3d_make(1, 2, 3);
    b = Vector3d_make(1, 3, 3);
    ccls(LogicalMask3d) eq = Vector3d_eq(a, b);
    assert(LogicalMask3d_x(eq) == true);   // 1==1
    assert(LogicalMask3d_y(eq) == false);  // 2!=3
    assert(LogicalMask3d_z(eq) == true);   // 3==3
    LogicalMask3d_destroy(eq);

    ccls(LogicalMask3d) gt = Vector3d_gt(a, b);
    assert(LogicalMask3d_x(gt) == false); // 1>1 false
    assert(LogicalMask3d_y(gt) == false); // 2>3 false
    assert(LogicalMask3d_z(gt) == false); // 3>3 false
    LogicalMask3d_destroy(gt);

    ccls(LogicalMask3d) lt = Vector3d_lt(a, b);
    assert(LogicalMask3d_x(lt) == false);
    assert(LogicalMask3d_y(lt) == true);  // 2<3
    assert(LogicalMask3d_z(lt) == false);
    LogicalMask3d_destroy(lt);

    ccls(LogicalMask3d) ge = Vector3d_ge(a, b);
    assert(LogicalMask3d_x(ge) == true);
    assert(LogicalMask3d_y(ge) == false);
    assert(LogicalMask3d_z(ge) == true);
    LogicalMask3d_destroy(ge);

    ccls(LogicalMask3d) le = Vector3d_le(a, b);
    assert(LogicalMask3d_x(le) == true);
    assert(LogicalMask3d_y(le) == true);
    assert(LogicalMask3d_z(le) == true);
    LogicalMask3d_destroy(le);

    ccls(LogicalMask3d) neq = Vector3d_neq(a, b);
    assert(LogicalMask3d_x(neq) == false);
    assert(LogicalMask3d_y(neq) == true);
    assert(LogicalMask3d_z(neq) == false);
    LogicalMask3d_destroy(neq);

    // scalar comparisons
    ccls(LogicalMask3d) seq = Vector3d_seq(a, 2.0f);
    assert(LogicalMask3d_x(seq) == false); // 1==2 false
    assert(LogicalMask3d_y(seq) == true);  // 2==2 true
    assert(LogicalMask3d_z(seq) == false); // 3==2 false
    LogicalMask3d_destroy(seq);

    ccls(LogicalMask3d) sgt = Vector3d_sgt(a, 2.0f);
    assert(LogicalMask3d_x(sgt) == false);
    assert(LogicalMask3d_y(sgt) == false);
    assert(LogicalMask3d_z(sgt) == true);
    LogicalMask3d_destroy(sgt);

    ccls(LogicalMask3d) slt = Vector3d_slt(a, 2.0f);
    assert(LogicalMask3d_x(slt) == true);
    assert(LogicalMask3d_y(slt) == false);
    assert(LogicalMask3d_z(slt) == false);
    LogicalMask3d_destroy(slt);

    ccls(LogicalMask3d) sge = Vector3d_sge(a, 2.0f);
    assert(LogicalMask3d_x(sge) == false);
    assert(LogicalMask3d_y(sge) == true);
    assert(LogicalMask3d_z(sge) == true);
    LogicalMask3d_destroy(sge);

    ccls(LogicalMask3d) sle = Vector3d_sle(a, 2.0f);
    assert(LogicalMask3d_x(sle) == true);
    assert(LogicalMask3d_y(sle) == true);
    assert(LogicalMask3d_z(sle) == false);
    LogicalMask3d_destroy(sle);

    ccls(LogicalMask3d) sneq = Vector3d_sneq(a, 2.0f);
    assert(LogicalMask3d_x(sneq) == true);
    assert(LogicalMask3d_y(sneq) == false);
    assert(LogicalMask3d_z(sneq) == true);
    LogicalMask3d_destroy(sneq);

    // toMask
    ccls(Vector3d) vmasktest = Vector3d_make(0.0f, 1.5f, -2.5f);
    ccls(LogicalMask3d) mask = Vector3d_toMask(vmasktest);
    assert(LogicalMask3d_x(mask) == false); // 0
    assert(LogicalMask3d_y(mask) == true);  // non-zero
    assert(LogicalMask3d_z(mask) == true);  // non-zero
    LogicalMask3d_destroy(mask);
    Vector3d_destroy(vmasktest);

    Vector3d_destroy(a); Vector3d_destroy(b);
}

// ------------------------------------------------------------
// LogicalMask3d tests
// ------------------------------------------------------------
void test_LogicalMask3d(void) {
    // Use vectors to create masks
    ccls(Vector3d) v1 = Vector3d_make(1, 2, 3);
    ccls(Vector3d) v2 = Vector3d_make(1, 0, 3);
    ccls(LogicalMask3d) mask_eq = Vector3d_eq(v1, v2); // x true, y false, z true

    // empty
    ccls(LogicalMask3d) empty = LogicalMask3d_empty();
    assert(LogicalMask3d_any(empty) == false);
    assert(LogicalMask3d_all(empty) == false);
    LogicalMask3d_destroy(empty);

    // copy
    ccls(LogicalMask3d) copy = LogicalMask3d_copy(mask_eq);
    assert(LogicalMask3d_x(copy) == true);
    assert(LogicalMask3d_y(copy) == false);
    assert(LogicalMask3d_z(copy) == true);
    LogicalMask3d_destroy(copy);

    // any, all
    assert(LogicalMask3d_any(mask_eq) == true);
    assert(LogicalMask3d_all(mask_eq) == false);

    // and
    ccls(LogicalMask3d) all_true = Vector3d_eq(v1, v1);
    ccls(LogicalMask3d) and_mask = LogicalMask3d_and(mask_eq, all_true);
    assert(LogicalMask3d_x(and_mask) == true);
    assert(LogicalMask3d_y(and_mask) == false);
    assert(LogicalMask3d_z(and_mask) == true);
    LogicalMask3d_destroy(and_mask);
    LogicalMask3d_destroy(all_true);

    // or
    ccls(LogicalMask3d) false_mask = LogicalMask3d_empty();
    ccls(LogicalMask3d) or_mask = LogicalMask3d_or(mask_eq, false_mask);
    assert(LogicalMask3d_x(or_mask) == true);
    assert(LogicalMask3d_y(or_mask) == false);
    assert(LogicalMask3d_z(or_mask) == true);
    LogicalMask3d_destroy(or_mask);

    // xor
    ccls(LogicalMask3d) xor_mask = LogicalMask3d_xor(mask_eq, false_mask);
    assert(LogicalMask3d_x(xor_mask) == true);
    assert(LogicalMask3d_y(xor_mask) == false);
    LogicalMask3d_destroy(xor_mask);
    LogicalMask3d_destroy(false_mask);

    // not
    ccls(LogicalMask3d) not_mask = LogicalMask3d_not(mask_eq);
    assert(LogicalMask3d_x(not_mask) == false);
    assert(LogicalMask3d_y(not_mask) == true);
    assert(LogicalMask3d_z(not_mask) == false);
    LogicalMask3d_destroy(not_mask);

    // assign
    ccls(Vector3d) vec = Vector3d_make(10, 20, 30);
    ccls(Vector3d) assigned = LogicalMask3d_assign(mask_eq, vec);
    // x true -> 10, y false -> 0, z true -> 30
    fassert(Vector3d_getX(assigned), 10.0f);
    fassert(Vector3d_getY(assigned), 0.0f);
    fassert(Vector3d_getZ(assigned), 30.0f);
    Vector3d_destroy(assigned);

    // combine
    ccls(Vector3d) tvec = Vector3d_make(1, 1, 1);
    ccls(Vector3d) fvec = Vector3d_make(0, 0, 0);
    ccls(Vector3d) combined = LogicalMask3d_combine(mask_eq, tvec, fvec);
    fassert(Vector3d_getX(combined), 1.0f);
    fassert(Vector3d_getY(combined), 0.0f);
    fassert(Vector3d_getZ(combined), 1.0f);
    Vector3d_destroy(combined);
    Vector3d_destroy(tvec);
    Vector3d_destroy(fvec);
    Vector3d_destroy(vec);

    // toChar
    char ch = LogicalMask3d_toChar(mask_eq);
    assert(ch == (char)0x05); // binary 101 -> 5

    // toVector
    ccls(Vector3d) maskvec = LogicalMask3d_toVector(mask_eq);
    fassert(Vector3d_getX(maskvec), 1.0f);
    fassert(Vector3d_getY(maskvec), 0.0f);
    fassert(Vector3d_getZ(maskvec), 1.0f);
    Vector3d_destroy(maskvec);

    LogicalMask3d_destroy(mask_eq);
    Vector3d_destroy(v1); Vector3d_destroy(v2);
}

// ------------------------------------------------------------
// Matrix3d tests
// ------------------------------------------------------------
void test_Matrix3d(void) {
    // --- constructors ---
    ccls(Matrix3d) eye = Matrix3d_eye();
    ccls(Vector3d) v = Vector3d_make(7, 8, 9);
    ccls(Vector3d) transformed = Matrix3d_apply(eye, v);
    fassert(Vector3d_getX(transformed), 7.0f);
    fassert(Vector3d_getY(transformed), 8.0f);
    fassert(Vector3d_getZ(transformed), 9.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(eye);

    // diag
    ccls(Matrix3d) diag = Matrix3d_diag(2.0f);
    transformed = Matrix3d_apply(diag, v);
    fassert(Vector3d_getX(transformed), 14.0f);
    fassert(Vector3d_getY(transformed), 16.0f);
    fassert(Vector3d_getZ(transformed), 18.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(diag);

    // fill
    ccls(Matrix3d) fillmat = Matrix3d_fill(3.0f);
    // apply
    transformed = Matrix3d_apply(fillmat, v);
    fassert(Vector3d_getX(transformed), 72.0f);
    fassert(Vector3d_getY(transformed), 72.0f);
    fassert(Vector3d_getZ(transformed), 72.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(fillmat);

    // copy
    ccls(Matrix3d) copy = Matrix3d_copy(diag = Matrix3d_diag(3.0f));
    transformed = Matrix3d_apply(copy, v);
    fassert(Vector3d_getX(transformed), 21.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(copy);
    Matrix3d_destroy(diag);

    // concatCols and concatRows
    ccls(Float3) c0 = Float3_make(1, 0, 0);
    ccls(Float3) c1 = Float3_make(0, 1, 0);
    ccls(Float3) c2 = Float3_make(0, 0, 1);
    ccls(Matrix3d) fromCols = Matrix3d_concatCols(c0, c1, c2);
    transformed = Matrix3d_apply(fromCols, v);
    fassert(Vector3d_getX(transformed), 7.0f);
    fassert(Vector3d_getY(transformed), 8.0f);
    fassert(Vector3d_getZ(transformed), 9.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(fromCols);
    Float3_destroy(c0); Float3_destroy(c1); Float3_destroy(c2);

    ccls(Float3) r0 = Float3_make(1, 0, 0);
    ccls(Float3) r1 = Float3_make(0, 1, 0);
    ccls(Float3) r2 = Float3_make(0, 0, 1);
    ccls(Matrix3d) fromRows = Matrix3d_concatRows(r0, r1, r2);
    transformed = Matrix3d_apply(fromRows, v);
    fassert(Vector3d_getX(transformed), 7.0f);
    fassert(Vector3d_getY(transformed), 8.0f);
    fassert(Vector3d_getZ(transformed), 9.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(fromRows);
    Float3_destroy(r0); Float3_destroy(r1); Float3_destroy(r2);

    // empty
    ccls(Matrix3d) empty_mat = Matrix3d_empty();
    transformed = Matrix3d_apply(empty_mat, v);
    fassert(Vector3d_getX(transformed), 0.0f);
    fassert(Vector3d_getY(transformed), 0.0f);
    fassert(Vector3d_getZ(transformed), 0.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(empty_mat);

    // --- in-place arithmetic ---
    ccls(Matrix3d) A = Matrix3d_diag(2.0f);
    ccls(Matrix3d) B = Matrix3d_diag(3.0f);

    // add_assign
    Matrix3d_add_assign(A, B);
    transformed = Matrix3d_apply(A, v);
    fassert(Vector3d_getX(transformed), 35.0f);
    fassert(Vector3d_getY(transformed), 40.0f);
    fassert(Vector3d_getZ(transformed), 45.0f);
    Vector3d_destroy(transformed);

    // sub_assign
    Matrix3d_sub_assign(A, B);
    transformed = Matrix3d_apply(A, v);
    fassert(Vector3d_getX(transformed), 14.0f);
    Vector3d_destroy(transformed);

    // mul_assign
    Matrix3d_mul_assign(A, B);
    transformed = Matrix3d_apply(A, v);
    A = Matrix3d_diag(2.0f);
    fassert(Vector3d_getX(transformed), 42.0f);
    fassert(Vector3d_getY(transformed), 48.0f);
    fassert(Vector3d_getZ(transformed), 54.0f);
    Vector3d_destroy(transformed);

    // div_assign
    ccls(Matrix3d) Af = Matrix3d_fill(6.0f);
    ccls(Matrix3d) Bf = Matrix3d_fill(2.0f);
    Matrix3d_div_assign(Af, Bf);
    transformed = Matrix3d_apply(Af, v);
    fassert(Vector3d_getX(transformed), 72.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(Af);
    Matrix3d_destroy(Bf);

    // smul_assign
    Matrix3d_smul_assign(A, 10.0f);
    transformed = Matrix3d_apply(A, v);
    fassert(Vector3d_getX(transformed), 140.0f);
    Vector3d_destroy(transformed);

    // sdiv_assign
    Matrix3d_sdiv_assign(A, 10.0f);
    transformed = Matrix3d_apply(A, v);
    fassert(Vector3d_getX(transformed), 14.0f);
    Vector3d_destroy(transformed);

    Matrix3d_destroy(A); Matrix3d_destroy(B);

    // --- non-assign arithmetic ---
    A = Matrix3d_diag(2.0f);
    B = Matrix3d_diag(3.0f);
    ccls(Matrix3d) C;

    C = Matrix3d_add(A, B);
    transformed = Matrix3d_apply(C, v);
    fassert(Vector3d_getX(transformed), 35.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(C);

    C = Matrix3d_sub(A, B);
    transformed = Matrix3d_apply(C, v);
    fassert(Vector3d_getX(transformed), -7.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(C);

    C = Matrix3d_mul(A, B);
    transformed = Matrix3d_apply(C, v);
    fassert(Vector3d_getX(transformed), 42.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(C);

    Af = Matrix3d_fill(6.0f);
    Bf = Matrix3d_fill(2.0f);
    C = Matrix3d_div(Af, Bf);
    transformed = Matrix3d_apply(C, v);
    fassert(Vector3d_getX(transformed), 72.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(C);
    Matrix3d_destroy(Af);
    Matrix3d_destroy(Bf);

    C = Matrix3d_smul(A, 5.0f);
    transformed = Matrix3d_apply(C, v);
    fassert(Vector3d_getX(transformed), 70.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(C);

    C = Matrix3d_sdiv(A, 2.0f);
    transformed = Matrix3d_apply(C, v);
    fassert(Vector3d_getX(transformed), 7.0f);
    Vector3d_destroy(transformed);
    Matrix3d_destroy(C);

    Matrix3d_destroy(A); Matrix3d_destroy(B);
    Vector3d_destroy(v);
}

int main(void) {
    test_Float3();
    test_Vector3d();
    test_LogicalMask3d();
    test_Matrix3d();
    printf("All tests passed!\n");
    return 0;
}