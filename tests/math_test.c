#include "agl_math.h"

void test_vec3f_add() {
	vec3f_t a = {1, 2, 3};
	vec3f_t b = {4, 5, 6};
	vec3f_add(&a, &b);
	agl_vm_assert(float_eq(a._m[0], 5.f, 1e-6f));
	agl_vm_assert(float_eq(a._m[1], 7.f, 1e-6f));
	agl_vm_assert(float_eq(a._m[2], 9.f, 1e-6f));
}

void test_vec3f_addscaled() {
	vec3f_t a = {1, 2, 3};
	vec3f_t b = {4, 5, 6};
	vec3f_addscaled(&a, &b, 0.5f);
	agl_vm_assert(float_eq(a._m[0], 3.f, 1e-6f));
	agl_vm_assert(float_eq(a._m[1], 4.5f, 1e-6f));
	agl_vm_assert(float_eq(a._m[2], 6.f, 1e-6f));
}

void test_vec3f_sub() {
	vec3f_t a = {1, 2, 3};
	vec3f_t b = {4, 5, 6};
	vec3f_sub(&a, &b);
	agl_vm_assert(float_eq(a._m[0], -3.f, 1e-6f));
	agl_vm_assert(float_eq(a._m[1], -3.f, 1e-6f));
	agl_vm_assert(float_eq(a._m[2], -3.f, 1e-6f));
}

void test_vec3f_mul() {
	vec3f_t a = {1, 2, 3};
	vec3f_t b = {4, 5, 6};
	vec3f_mul(&a, &b);
	agl_vm_assert(float_eq(a._m[0], 4.f, 1e-6f));
	agl_vm_assert(float_eq(a._m[1], 10.f, 1e-6f));
	agl_vm_assert(float_eq(a._m[2], 18.f, 1e-6f));
}

void test_vec3f_div() {
	vec3f_t a = {4, 10, 18};
	vec3f_t b = {2, 5, 6};
	vec3f_div(&a, &b);
	agl_vm_assert(float_eq(a._m[0], 2.f, 1e-6f));
	agl_vm_assert(float_eq(a._m[1], 2.f, 1e-6f));
	agl_vm_assert(float_eq(a._m[2], 3.f, 1e-6f));
}

void test_quatf_fromaxisangle() {
	vec3f_t axis = {0, 1, 0};
	float angle = M_PI / 2; // 90 degrees
	quatf_t q;
	quatf_fromaxisangle(&q, &axis, angle);
	vec3f_t v = {1, 0, 0};
	vec3f_t r;
	quatf_apply(&r, &q, &v);
	agl_vm_assert(float_eq(r._m[0], 0.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[1], 0.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[2], -1.f, 1e-6f));
}

void test_quatf_fromvectors() {
	vec3f_t a = {1, 0, 0};
	vec3f_t b = {0, 1, 0};
	quatf_t q;
	quatf_fromvectors(&q, &a, &b);
	vec3f_t r;
	quatf_apply(&r, &q, &a);
	agl_vm_assert(float_eq(r._m[0], 0.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[1], 1.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[2], 0.f, 1e-6f));
}

void test_quatf_fromvectors_parallel() {
	vec3f_t a = {1, 0, 0};
	vec3f_t b = {1, 0, 0};
	quatf_t q;
	quatf_fromvectors(&q, &a, &b);
	vec3f_t r;
	quatf_apply(&r, &q, &a);
	agl_vm_assert(float_eq(r._m[0], 1.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[1], 0.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[2], 0.f, 1e-6f));
}

void test_quatf_fromvectors_antiparallel() {
	vec3f_t a = {1, 0, 0};
	vec3f_t b = {-1, 0, 0};
	quatf_t q;
	quatf_fromvectors(&q, &a, &b);
	vec3f_t r;
	quatf_apply(&r, &q, &a);
	agl_vm_assert(float_eq(r._m[0], -1.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[1], 0.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[2], 0.f, 1e-6f));
}

void test_mat3f_mul() {
	mat3f_t a = {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
	mat3f_t b = {{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}}};
	mat3f_t m;
	mat3f_mul(&m, &a, &b);
	agl_vm_assert(float_eq(m._m[0][0], 90.f, 1e-6f));
	agl_vm_assert(float_eq(m._m[0][1], 114.f, 1e-6f));
	agl_vm_assert(float_eq(m._m[0][2], 138.f, 1e-6f));
	agl_vm_assert(float_eq(m._m[1][0], 54.f, 1e-6f));
	agl_vm_assert(float_eq(m._m[1][1], 69.f, 1e-6f));
	agl_vm_assert(float_eq(m._m[1][2], 84.f, 1e-6f));
	agl_vm_assert(float_eq(m._m[2][0], 18.f, 1e-6f));
	agl_vm_assert(float_eq(m._m[2][1], 24.f, 1e-6f));
	agl_vm_assert(float_eq(m._m[2][2], 30.f, 1e-6f));
}

void test_mat3f_mulvec3f() {
	mat3f_t m = {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
	vec3f_t v = {1, 2, 3};
	vec3f_t r;
	mat3f_mulvec3f(&r, &m, &v);
	agl_vm_assert(float_eq(r._m[0], 30.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[1], 36.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[2], 42.f, 1e-6f));
}

void test_vec3f_mulmat3f() {
	vec3f_t v = {1, 2, 3};
	mat3f_t m = {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
	vec3f_t r;
	vec3f_mulmat3f(&r, &v, &m);
	agl_vm_assert(float_eq(r._m[0], 14.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[1], 32.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[2], 50.f, 1e-6f));
}

void test_mat3f_fromquat() {
	quatf_t q;
	quatf_fromaxisangle(&q, &(vec3f_t){0, 1, 0}, M_PI / 2);
	mat3f_t m;
	mat3f_fromquat(&m, &q);
	vec3f_t v = {1, 0, 0};
	vec3f_t r;
	mat3f_mulvec3f(&r, &m, &v);
	agl_vm_assert(float_eq(r._m[0], 0.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[1], 0.f, 1e-6f));
	agl_vm_assert(float_eq(r._m[2], -1.f, 1e-6f));
}

int main() {
	test_vec3f_add();
	test_vec3f_addscaled();
	test_vec3f_sub();
	test_vec3f_mul();
	test_vec3f_div();
	test_quatf_fromaxisangle();
	test_quatf_fromvectors();
	test_quatf_fromvectors_parallel();
	test_quatf_fromvectors_antiparallel();
	test_mat3f_mul();
	test_mat3f_mulvec3f();
	test_vec3f_mulmat3f();
	test_mat3f_fromquat();
	return 0;
}

#define AGL_MATH_IMPLEMENTATION
#include "agl_math.h"