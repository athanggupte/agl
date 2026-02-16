// agl_math.h - v0.1.0 - AGL Math Library
//
// PURPOSE
//   AGL's math library, providing vector, quaternion, and matrix types and operations.
//
// USAGE
//   Scalar types are named <basetype>f_t, e.g. vec3f_t, quatf_t.
//   Vector types are named <basetype>v_t, e.g. vec3v_t, quatv_t.
//   Scalar operations are inline so do not require a separate implementation file. Vector operations require an implementation file.
//   To use the vector operations, #define AGL_MATH_IMPLEMENTATION before including this file in *one* C or C++ file to create the implementation.
//
//
// MIT License
//   Copyright (c) 2026 Athang Gupte
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//   SOFTWARE.

#ifndef AGL_MATH_H
#define AGL_MATH_H

#include <immintrin.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <stdbool.h>

#define alignas(n) __attribute__((aligned(n)))

#ifndef AGL_MATH_ENABLE_ASSERTS
#define AGL_MATH_ENABLE_ASSERTS _DEBUG
#endif

#if AGL_MATH_ENABLE_ASSERTS
#	include <stdio.h>
#	define agl_vm_assert(cond) do { if (!(cond)) { fprintf(stderr, "Assertion failed: %s\n", #cond); __debugbreak(); } } while (0)
#else
#	define agl_vm_assert(cond)
#endif

#define isaligned16(v) ((((uintptr_t)(&(v))) & 0xF) == 0)

#define FLOAT_FMT "%0.3f"
#define VEC3_FMT FLOAT_FMT ", " FLOAT_FMT ", " FLOAT_FMT
#define VEC3_ARG(v) (v)._m[0], (v)._m[1], (v)._m[2]
#define VEC4_FMT FLOAT_FMT ", " FLOAT_FMT ", " FLOAT_FMT ", " FLOAT_FMT
#define VEC4_ARG(v) (v)._m[0], (v)._m[1], (v)._m[2], (v)._m[3]

inline bool float_eq(float a, float b, float eps) {
    float diff = fabsf(a - b);
    if (diff < eps)
        return true;
    a = fabsf(a);
    b = fabsf(b);
    float largest = (b > a) ? b : a;
    return (diff <= largest * eps);
}

inline void swapf(float *a, float *b) {
    float tmp; tmp = *a; *a = *b; *b = tmp;
}

inline float clampf(float f, float fmin, float fmax) {
    float r = min(f, fmax);
    r = max(r, fmin);
    return r;
}

typedef struct vec3f_t vec3f_t;
typedef struct vec4f_t vec4f_t;
typedef struct quatf_t quatf_t;
typedef struct mat3f_t mat3f_t;

struct vec3f_t { alignas(16) float _m[4]; };
struct vec4f_t { alignas(16) float _m[4]; };
struct quatf_t { alignas(16) float _m[4]; };
struct mat3f_t { alignas(16) float _m[4][3]; };

#define vec3f(x,y,z)    ((vec3f_t){(x),(y),(z),(0)})
#define vec4f(x,y,z,w)  ((vec4f_t){(x),(y),(z),(w)})
#define quatf(x,y,z,w)  ((quatf_t){(x),(y),(z),(w)})
#define mat3f(m00,m01,m02,m10,m11,m12,m20,m21,m22) ((mat3f_t){{{(m00),(m01),(m02)},{(m10),(m11),(m12)},{(m20),(m21),(m22)}}})

inline void vec3f_scale(vec3f_t *v, float s) {
    v->_m[0] *= s;
    v->_m[1] *= s;
    v->_m[2] *= s;
}

inline void vec3f_add(vec3f_t *v, const vec3f_t *b) {
    v->_m[0] += b->_m[0];
    v->_m[1] += b->_m[1];
    v->_m[2] += b->_m[2];
}

inline void vec3f_addscaled(vec3f_t *v, const vec3f_t *b, float s) {
    v->_m[0] += s * b->_m[0];
    v->_m[1] += s * b->_m[1];
    v->_m[2] += s * b->_m[2];
}

inline void vec3f_sub(vec3f_t *v, const vec3f_t *b) {
    v->_m[0] -= b->_m[0];
    v->_m[1] -= b->_m[1];
    v->_m[2] -= b->_m[2];
}

inline void vec3f_mul(vec3f_t *v, const vec3f_t *b) {
    v->_m[0] *= b->_m[0];
    v->_m[1] *= b->_m[1];
    v->_m[2] *= b->_m[2];
}

inline void vec3f_div(vec3f_t *v, const vec3f_t *b) {
    agl_vm_assert(b->_m[0] != 0 && b->_m[1] != 0 && b->_m[2] != 0);
    v->_m[0] /= b->_m[0];
    v->_m[1] /= b->_m[1];
    v->_m[2] /= b->_m[2];
}

inline void vec3f_add2(vec3f_t *v, const vec3f_t *a, const vec3f_t *b) {
    v->_m[0] = a->_m[0] + b->_m[0];
    v->_m[1] = a->_m[1] + b->_m[1];
    v->_m[2] = a->_m[2] + b->_m[2];
}

inline void vec3f_sub2(vec3f_t *v, const vec3f_t *a, const vec3f_t *b) {
    v->_m[0] = a->_m[0] - b->_m[0];
    v->_m[1] = a->_m[1] - b->_m[1];
    v->_m[2] = a->_m[2] - b->_m[2];
}

inline void vec3f_mul2(vec3f_t *v, const vec3f_t *a, const vec3f_t *b) {
    v->_m[0] = a->_m[0] * b->_m[0];
    v->_m[1] = a->_m[1] * b->_m[1];
    v->_m[2] = a->_m[2] * b->_m[2];
}

inline void vec3f_div2(vec3f_t *v, const vec3f_t *a, const vec3f_t *b) {
    agl_vm_assert(b->_m[0] != 0 && b->_m[1] != 0 && b->_m[2] != 0);
    v->_m[0] = a->_m[0] / b->_m[0];
    v->_m[1] = a->_m[1] / b->_m[1];
    v->_m[2] = a->_m[2] / b->_m[2];
}

inline float vec3f_dot(const vec3f_t *a, const vec3f_t *b) {
    return a->_m[0] * b->_m[0]
         + a->_m[1] * b->_m[1]
         + a->_m[2] * b->_m[2];
}

inline float vec3f_sqrlen(const vec3f_t *v) {
    return vec3f_dot(v, v);
}

inline float vec3f_len(const vec3f_t *v) {
    return sqrtf(vec3f_sqrlen(v));
}

inline void vec3f_normalize(vec3f_t *v) {
    vec3f_scale(v, 1/vec3f_len(v));
}

inline void vec3f_cross(vec3f_t *v, const vec3f_t *a, const vec3f_t *b) {
	float ax= a->_m[0], ay = a->_m[1], az = a->_m[2];
	float bx= b->_m[0], by = b->_m[1], bz = b->_m[2];
    v->_m[0] = ay * bz - az * by;
    v->_m[1] = az * bx - ax * bz;
    v->_m[2] = ax * by - ay * bx;
}

inline void vec3f_recip(vec3f_t *vr, const vec3f_t *v) {
    vr->_m[0] = 1.f / v->_m[0];
    vr->_m[1] = 1.f / v->_m[1];
    vr->_m[2] = 1.f / v->_m[2];
}

inline vec3f_t vec3f_urand() {
    const float RAND_MAX_F = (float)RAND_MAX;
    return (vec3f_t) {
        ((float)rand()) / RAND_MAX_F,
        ((float)rand()) / RAND_MAX_F,
        ((float)rand()) / RAND_MAX_F,
    };
}

inline vec3f_t vec3f_srand() {
    const float RAND_MAX_F = (float)RAND_MAX;
    return (vec3f_t) {
        ((float)rand()) / RAND_MAX_F * 2.f - 1.f,
        ((float)rand()) / RAND_MAX_F * 2.f - 1.f,
        ((float)rand()) / RAND_MAX_F * 2.f - 1.f,
    };
}

inline void quatf_inv(quatf_t *q) {
    q->_m[0] = -q->_m[0];
    q->_m[1] = -q->_m[1];
    q->_m[2] = -q->_m[2];
}

inline void quatf_add(quatf_t *q, const quatf_t *b) {
	q->_m[0] += b->_m[0];
	q->_m[1] += b->_m[1];
	q->_m[2] += b->_m[2];
	q->_m[3] += b->_m[3];
}

inline void quatf_addscaled(quatf_t *q, const quatf_t *b, float s) {
    q->_m[0] += s * b->_m[0];
    q->_m[1] += s * b->_m[1];
    q->_m[2] += s * b->_m[2];
    q->_m[3] += s * b->_m[3];
}

inline void quatf_sub(quatf_t *q, const quatf_t *b) {
	q->_m[0] -= b->_m[0];
	q->_m[1] -= b->_m[1];
	q->_m[2] -= b->_m[2];
	q->_m[3] -= b->_m[3];
}

inline void quatf_mul2(quatf_t *q, const quatf_t *a, const quatf_t *b) {
    float x1 = a->_m[0], y1 = a->_m[1], z1 = a->_m[2], w1 = a->_m[3];
    float x2 = b->_m[0], y2 = b->_m[1], z2 = b->_m[2], w2 = b->_m[3];
    q->_m[3] = w1*w2 - x1*x2 - y1*y2 - z1*z2;
    q->_m[0] = w1*x2 + x1*w2 + y1*z2 - z1*y2;
    q->_m[1] = w1*y2 - x1*z2 + y1*w2 + z1*x2;
    q->_m[2] = w1*z2 + x1*y2 - y1*x2 + z1*w2;
}

inline float quatf_sqrlen(const quatf_t *q) {
    float x = q->_m[0], y = q->_m[1], z = q->_m[2], w = q->_m[3];
    return x*x + y*y + z*z + w*w;
}

inline float quatf_len(const quatf_t *q) {
    return sqrtf(quatf_sqrlen(q));
}

inline void quatf_normalize(quatf_t *q) {
    float norm = quatf_len(q);
    q->_m[0] /= norm;
    q->_m[1] /= norm;
    q->_m[2] /= norm;
    q->_m[3] /= norm;
}

inline void quatf_apply(vec3f_t *r, const quatf_t *q, const vec3f_t *v) {
    agl_vm_assert(float_eq(quatf_sqrlen(q), 1.f, 1e-6f));
	quatf_t qv = quatf(v->_m[0], v->_m[1], v->_m[2], 0.f);
	quatf_t qinv = *q;
	quatf_inv(&qinv);
	quatf_t tmp;
	quatf_mul2(&tmp, q, &qv);
	quatf_mul2((quatf_t*)r, &tmp, &qinv);
}

inline void quatf_applyinv(vec3f_t *r, const quatf_t *q, const vec3f_t *v) {
    agl_vm_assert(float_eq(quatf_sqrlen(q), 1.f, 1e-6f));
    quatf_t qv = quatf(v->_m[0], v->_m[1], v->_m[2], 0.f);
	quatf_t qinv = *q;
	quatf_inv(&qinv);
	quatf_t tmp;
	quatf_mul2(&tmp, &qinv, &qv);
	quatf_mul2((quatf_t*)r, &tmp, q);
}

inline void quatf_fromaxisangle(quatf_t *q, const vec3f_t *axis, float angle) {
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    q->_m[3] = c;
    q->_m[0] = s * axis->_m[0];
    q->_m[1] = s * axis->_m[1];
    q->_m[2] = s * axis->_m[2];
    quatf_normalize(q);
}

inline void quatf_fromvectors(quatf_t *q, const vec3f_t *a, const vec3f_t *b) {
    vec3f_t u = *a;
    vec3f_t v = *b;
    vec3f_normalize(&u);
    vec3f_normalize(&v);
    vec3f_t axis = vec3f(0,0,0);
    vec3f_cross(&axis, &u, &v);
    float costheta = vec3f_dot(&u, &v);
    if (float_eq(costheta, 1.f, FLT_EPSILON)) {
        *q = quatf(0,0,0,1);
        return;
    }
    if (float_eq(costheta, -1.f, 1e-6)) {
        if (float_eq(u._m[2], 1.f, FLT_EPSILON)) // u is parallel to (0,0,1)
            vec3f_cross(&axis, &u, &vec3f(1,0,0));
        else
            vec3f_cross(&axis, &u, &vec3f(0,0,1));
    }
    float theta = acosf(costheta);
    vec3f_normalize(&axis);
    quatf_fromaxisangle(q, &axis, theta);
}

inline void mat3f_fromquat(mat3f_t *m, const quatf_t *q) {
    *m = (mat3f_t){0};
    float q0 = q->_m[3], q1 = q->_m[0], q2 = q->_m[1], q3 = q->_m[2];
    m->_m[0][0] = 1 - 2*q2*q2 - 2*q3*q3;
	m->_m[1][0] = 2*q1*q2 - 2*q0*q3;
	m->_m[2][0] = 2*q1*q3 + 2*q0*q2;
	m->_m[0][1] = 2*q1*q2 + 2*q0*q3;
	m->_m[1][1] = 1 - 2*q1*q1 - 2*q3*q3;
	m->_m[2][1] = 2*q2*q3 - 2*q0*q1;
	m->_m[0][2] = 2*q1*q3 - 2*q0*q2;
	m->_m[1][2] = 2*q2*q3 + 2*q0*q1;
	m->_m[2][2] = 1 - 2*q1*q1 - 2*q2*q2;
}

inline void mat3f_fromdiag(mat3f_t *m, const vec3f_t *v) {
    *m = (mat3f_t){0};
    m->_m[0][0] = v->_m[0];
    m->_m[1][1] = v->_m[1];
    m->_m[2][2] = v->_m[2];
}

inline void mat3f_fromcols(mat3f_t *m, const vec3f_t *col0, const vec3f_t *col1, const vec3f_t *col2) {
	m->_m[0][0] = col0->_m[0];
	m->_m[0][1] = col0->_m[1];
	m->_m[0][2] = col0->_m[2];
	m->_m[1][0] = col1->_m[0];
	m->_m[1][1] = col1->_m[1];
	m->_m[1][2] = col1->_m[2];
	m->_m[2][0] = col2->_m[0];
	m->_m[2][1] = col2->_m[1];
	m->_m[2][2] = col2->_m[2];
}

inline void mat3f_transpose(mat3f_t *m) {
    swapf(&m->_m[0][1], &m->_m[1][0]);
    swapf(&m->_m[0][2], &m->_m[2][0]);
    swapf(&m->_m[1][2], &m->_m[2][1]);
}

inline void mat3f_mul(mat3f_t *m, const mat3f_t *a, const mat3f_t *b) {
    m->_m[0][0] = a->_m[0][0] * b->_m[0][0] + a->_m[1][0] * b->_m[0][1] + a->_m[2][0] * b->_m[0][2];
    m->_m[0][1] = a->_m[0][1] * b->_m[0][0] + a->_m[1][1] * b->_m[0][1] + a->_m[2][1] * b->_m[0][2];
    m->_m[0][2] = a->_m[0][2] * b->_m[0][0] + a->_m[1][2] * b->_m[0][1] + a->_m[2][2] * b->_m[0][2];
    m->_m[1][0] = a->_m[0][0] * b->_m[1][0] + a->_m[1][0] * b->_m[1][1] + a->_m[2][0] * b->_m[1][2];
    m->_m[1][1] = a->_m[0][1] * b->_m[1][0] + a->_m[1][1] * b->_m[1][1] + a->_m[2][1] * b->_m[1][2];
    m->_m[1][2] = a->_m[0][2] * b->_m[1][0] + a->_m[1][2] * b->_m[1][1] + a->_m[2][2] * b->_m[1][2];
    m->_m[2][0] = a->_m[0][0] * b->_m[2][0] + a->_m[1][0] * b->_m[2][1] + a->_m[2][0] * b->_m[2][2];
    m->_m[2][1] = a->_m[0][1] * b->_m[2][0] + a->_m[1][1] * b->_m[2][1] + a->_m[2][1] * b->_m[2][2];
    m->_m[2][2] = a->_m[0][2] * b->_m[2][0] + a->_m[1][2] * b->_m[2][1] + a->_m[2][2] * b->_m[2][2];
}

// v(3,1) = m(3,3) * b(3,1)
inline void mat3f_mulvec3f(vec3f_t *v, const mat3f_t *m, const vec3f_t *b) {
    v->_m[0] = m->_m[0][0] * b->_m[0] + m->_m[1][0] * b->_m[1] + m->_m[2][0] * b->_m[2];
    v->_m[1] = m->_m[0][1] * b->_m[0] + m->_m[1][1] * b->_m[1] + m->_m[2][1] * b->_m[2];
    v->_m[2] = m->_m[0][2] * b->_m[0] + m->_m[1][2] * b->_m[1] + m->_m[2][2] * b->_m[2];
}

// v'(1,3) = a'(1,3) * m(3,3)
inline void vec3f_mulmat3f(vec3f_t *v, const vec3f_t *a, const mat3f_t *m) {
    v->_m[0] = a->_m[0] * m->_m[0][0] + a->_m[1] * m->_m[0][1] + a->_m[2] * m->_m[0][2];
    v->_m[1] = a->_m[0] * m->_m[1][0] + a->_m[1] * m->_m[1][1] + a->_m[2] * m->_m[1][2];
    v->_m[2] = a->_m[0] * m->_m[2][0] + a->_m[1] * m->_m[2][1] + a->_m[2] * m->_m[2][2];
}

typedef struct vec3v_t vec3v_t;
typedef struct vec4v_t vec4v_t;
typedef struct quatv_t quatv_t;

struct vec3v_t { __m128 _m; };
struct vec4v_t { __m128 _m; };
struct quatv_t { __m128 _m; };

vec3v_t vec3v_load_aligned(const vec3f_t *f);
vec3v_t vec3v_load_unaligned(const float *f);
void vec3v_store_aligned(const vec3v_t *v, vec3f_t *f);
void vec3v_store_unaligned(const vec3v_t *v, float *f);
vec4v_t vec4v_load_aligned(const vec4f_t *f);
vec4v_t vec4v_load_unaligned(const float *f);
void vec4v_store_aligned(const vec4v_t *v, vec4f_t *f);
void vec4v_store_unaligned(const vec4v_t *v, float *f);
quatv_t quatv_load_aligned(const quatf_t *f);
quatv_t quatv_load_unaligned(const float *f);
void quatv_store_aligned(const quatv_t *v, quatf_t *f);
void quatv_store_unaligned(const quatv_t *v, float *f);

#define vec3v_load(f) (vec3v_load_unaligned(f));
#define vec3v_store(v, f) (vec3v_store_unaligned((v), (f)));
#define vec4v_load(f) (vec4v_load_unaligned(f));
#define vec4v_store(v, f) (vec4v_store_unaligned((v), (f)));
#define quatv_load(f) (quatv_load_unaligned(f));
#define quatv_store(v, f) (quatv_store_unaligned((v), (f)));

vec3v_t vec3v_add(const vec3v_t *a, const vec3v_t *b);
vec4v_t vec4v_add(const vec4v_t *a, const vec4v_t *b);
vec3v_t vec3v_sub(const vec3v_t *a, const vec3v_t *b);
vec4v_t vec4v_sub(const vec4v_t *a, const vec4v_t *b);
float vec3v_dot(const vec3v_t *a, const vec3v_t *b);
void vec3v_dot3(const vec3v_t *a, const vec3v_t *b, vec3v_t *r);
void vec4v_dot(const vec4v_t *a, const vec4v_t *b, vec4v_t *r);
void vec4v_dot4(const vec4v_t *a, const vec4v_t *b, vec4v_t *r);
void vec3v_cross(const vec3v_t *a, const vec3v_t *b, vec3v_t *r);
void vec4v_cross(const vec4v_t *a, const vec4v_t *b, vec4v_t *r);

void quatv_conjugate(const quatv_t *q, quatv_t *qc);
quatv_t quatv_from_axis_angle(const vec4v_t *axisangle);
vec4v_t quatv_to_axis_angle(const quatv_t *q);

#endif // AGL_MATH_H

#ifdef AGL_MATH_IMPLEMENTATION

#define XCONCAT(x,y) x##y
#define CONCAT(x,y) XCONCAT(x,y)

#define VECTOR_TYPE_BASE(basetype) CONCAT(basetype,v)
#define VECTOR_TYPE_FULL(basetype) CONCAT(basetype,v_t)
#define SCALAR_TYPE_BASE(basetype) CONCAT(basetype,f)
#define SCALAR_TYPE_FULL(basetype) CONCAT(basetype,f_t)

#define FOR_EACH_BASETYPE(MACRO)    \
    MACRO(vec3);                    \
    MACRO(vec4);                    \
    MACRO(quat)

#define LOAD_ALIGNED_IMPL(basetype) \
    VECTOR_TYPE_FULL(basetype) CONCAT(VECTOR_TYPE_BASE(basetype),_load_aligned)(const SCALAR_TYPE_FULL(basetype) *f) { return (VECTOR_TYPE_FULL(basetype)){ _mm_load_ps(f->_m) }; }

FOR_EACH_BASETYPE(LOAD_ALIGNED_IMPL);

#undef LOAD_ALIGNED_IMPL

#define LOAD_UNALIGNED_IMPL(basetype) \
    VECTOR_TYPE_FULL(basetype) CONCAT(VECTOR_TYPE_BASE(basetype),_load_unaligned)(const float *f) { return (VECTOR_TYPE_FULL(basetype)){ _mm_loadu_ps(f) }; }

FOR_EACH_BASETYPE(LOAD_UNALIGNED_IMPL);

#undef LOAD_UNALIGNED_IMPL

#define STORE_ALIGNED_IMPL(basetype) \
    void CONCAT(VECTOR_TYPE_BASE(basetype),_store_aligned)(const VECTOR_TYPE_FULL(basetype) *v, SCALAR_TYPE_FULL(basetype) *f) { agl_vm_assert(isaligned16(f->_m)); _mm_store_ps(f->_m, v->_m); }

FOR_EACH_BASETYPE(STORE_ALIGNED_IMPL);

#undef STORE_ALIGNED_IMPL

#define STORE_UNALIGNED_IMPL(basetype) \
    void CONCAT(VECTOR_TYPE_BASE(basetype),_store_unaligned)(const VECTOR_TYPE_FULL(basetype) *v, float *f) { _mm_storeu_ps(f, v->_m); }

FOR_EACH_BASETYPE(STORE_UNALIGNED_IMPL);

vec3v_t vec3v_add(const vec3v_t *a, const vec3v_t *b) {
    return (vec3v_t){ _mm_add_ps(a->_m, b->_m) };
}

vec4v_t vec4v_add(const vec4v_t *a, const vec4v_t *b) {
    return (vec4v_t){ _mm_add_ps(a->_m, b->_m) };
}

vec3v_t vec3v_sub(const vec3v_t *a, const vec3v_t *b) {
    return (vec3v_t){ _mm_sub_ps(a->_m, b->_m) };
}

vec4v_t vec4v_sub(const vec4v_t *a, const vec4v_t *b) {
    return (vec4v_t){ _mm_sub_ps(a->_m, b->_m) };
}

float vec3v_dot(const vec3v_t *a, const vec3v_t *b) {
    __m128 dp = _mm_dp_ps(a->_m, b->_m, 0x71);
    alignas(16) float res[4];
    _mm_store1_ps(res, dp);
    return res[0];
}

#define _MM_BLEND(x,y,z,w) ((x)|((y)<<1)|((z)<<2)|((w)<<3))

void quatv_conjugate(const quatv_t *q, quatv_t *qc) {
    const vec3v_t vzero = vec3v_load(((float[]){0.f, 0.f, 0.f, 0.f}));
    __m128 neg = _mm_sub_ps(vzero._m, q->_m);
    qc->_m = _mm_blend_ps(neg, q->_m, _MM_BLEND(0,0,0,1));
}

#undef STORE_UNALIGNED_IMPL

#endif // AGL_MATH_IMPLEMENTATION