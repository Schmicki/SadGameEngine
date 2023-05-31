#pragma once

#include "platform.h"

/*************************************************************************************************/

typedef struct vec2_t vec2_t;

typedef struct vec3_t vec3_t;

typedef struct vec4_t vec4_t;

typedef struct vec4_t quat_t;

typedef struct mat3_t mat3_t;

typedef struct mat4_t mat4_t;

typedef struct transform_t transform_t;

typedef struct aabb_t aabb_t;

/*************************************************************************************************/

struct vec2_t
{
	flt_t x;
	flt_t y;
};

/*************************************************************************************************/

struct vec3_t
{
	flt_t x;
	flt_t y;
	flt_t z;
};

/*************************************************************************************************/

struct vec4_t
{
	flt_t x;
	flt_t y;
	flt_t z;
	flt_t w;
};

/*************************************************************************************************/

struct mat3_t
{
	flt_t m[9];
};

/*************************************************************************************************/

struct mat4_t
{
	flt_t m[16];
};

/*************************************************************************************************/

struct transform_t
{
	vec3_t location;
	quat_t rotation;
	vec3_t scale;
};

/*************************************************************************************************/

struct aabb_t
{
	vec3_t min, max;
};

/*************************************************************************************************/

vec2_t vec2_set(flt_t x, flt_t y);
vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);
vec2_t vec2_mul(vec2_t a, flt_t v);
vec2_t vec2_div(vec2_t a, flt_t v);
flt_t vec2_dot(vec2_t a, vec2_t b);
flt_t vec2_len(vec2_t a);
vec2_t vec2_unit(vec2_t a);
vec2_t vec2_lerp(vec2_t from, vec2_t to, flt_t alpha);
/* vec2_t vec2_rotate(vec2_t a, flt_t r); */
/* vec2_t vec2_transform(vec2_t a, mat3_t t); */
i32_t vec2_cmp(vec2_t a, vec2_t b);

/*************************************************************************************************/

vec3_t vec3_set(flt_t x, flt_t y, flt_t z);
vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);
vec3_t vec3_mul(vec3_t a, flt_t v);
vec3_t vec3_div(vec3_t a, flt_t v);
flt_t vec3_dot(vec3_t a, vec3_t b);
vec3_t vec3_cross(vec3_t a, vec3_t b);
flt_t vec3_len(vec3_t a);
vec3_t vec3_unit(vec3_t a);
vec3_t vec3_lerp(vec3_t from, vec3_t to, flt_t alpha);
vec3_t vec3_rotate(vec3_t a, quat_t r);
vec3_t vec3_transform(vec3_t a, mat4_t t);
i32_t vec3_cmp(vec3_t a, vec3_t b);

/*************************************************************************************************/

vec4_t vec4_set(flt_t x, flt_t y, flt_t z, flt_t w);
vec4_t vec4_add(vec4_t a, vec4_t b);
vec4_t vec4_sub(vec4_t a, vec4_t b);
vec4_t vec4_mul(vec4_t a, flt_t v);
vec4_t vec4_div(vec4_t a, flt_t v);
flt_t vec4_dot(vec4_t a, vec4_t b);
flt_t vec4_len(vec4_t a);
vec4_t vec4_unit(vec4_t a);
vec4_t vec4_lerp(vec4_t from, vec4_t to, flt_t alpha);
vec4_t vec4_transform(vec4_t a, mat4_t t);
i32_t vec4_cmp(vec4_t a, vec4_t b);

/*************************************************************************************************/

quat_t quat_euler_angles(vec3_t angles);
quat_t quat_axis_angle	(vec3_t axis, flt_t angle);
quat_t quat_add(quat_t a, quat_t b);
quat_t quat_sub(quat_t a, quat_t b);
quat_t quat_mul(quat_t a, flt_t v);
quat_t quat_div(quat_t a, flt_t v);
flt_t quat_dot(quat_t a, quat_t b);
flt_t quat_len(quat_t a);
quat_t quat_conj(quat_t a);
quat_t quat_inv(quat_t a);
quat_t quat_unit(quat_t a);
quat_t quat_lerp(quat_t from, quat_t to, flt_t alpha);
quat_t quat_slerp(quat_t from, quat_t to, flt_t alpha);
quat_t quat_slerpl(quat_t from, quat_t to, flt_t alpha);
quat_t quat_nlerp(quat_t from, quat_t to, flt_t alpha);
quat_t quat_rotate(quat_t a, quat_t r);

/*************************************************************************************************/

mat3_t mat3_add(mat3_t a, mat3_t b);
mat3_t mat3_sub(mat3_t a, mat3_t b);
mat3_t mat3_mul(mat3_t a, mat3_t b);

/*************************************************************************************************/

mat4_t mat4_translation(vec3_t t);
mat4_t mat4_rotation(quat_t r);
mat4_t mat4_scale(vec3_t s);
mat4_t mat4_model(transform_t transform);
mat4_t mat4_view(vec3_t location, vec3_t rotation);
mat4_t mat4_mvp(mat4_t model, mat4_t view, mat4_t projection);
/* 'far' <= abs('near') to get infinite far-plane. 'near' < 0 to reverse z. */
mat4_t mat4_perspective_vk(flt_t fov, flt_t ratio, flt_t near, flt_t far);
/* 'far' <= abs('near') to get infinite far-plane. 'near' < 0 to reverse z. */
mat4_t mat4_perspective_gl(flt_t fov, flt_t ratio, flt_t near, flt_t far);
/* 'far' <= abs('near') to get infinite far-plane. 'near' < 0 to reverse z. */
mat4_t mat4_perspective_gu(flt_t fov, flt_t ratio, flt_t near, flt_t far);
mat4_t mat4_add(mat4_t a, mat4_t b);
mat4_t mat4_sub(mat4_t a, mat4_t b);
mat4_t mat4_mul(mat4_t a, mat4_t b);
mat4_t mat4_transpose(mat4_t a);

/*************************************************************************************************/

#define PI (flt_t)3.141592653589793
#define flt_rtod(r) (r * ((flt_t)180.0 / PI))
#define flt_dtor(d) (d * (PI / (flt_t)180.0))

flt_t flt_abs(flt_t v);
flt_t flt_min(flt_t a, flt_t b);
flt_t flt_max(flt_t a, flt_t b);
flt_t flt_trunc(flt_t v);
flt_t flt_round(flt_t v);
flt_t flt_mod(flt_t v, flt_t mod);
flt_t flt_clamp(flt_t v, flt_t min, flt_t max);
flt_t flt_sin(flt_t v);
flt_t flt_asin(flt_t v);
flt_t flt_cos(flt_t v);
flt_t flt_acos(flt_t v);
flt_t flt_tan(flt_t v);
flt_t flt_atan(flt_t v);
flt_t flt_sqrt(flt_t v);
flt_t flt_pow(flt_t v, flt_t exp);
flt_t flt_log2(flt_t v);

/*************************************************************************************************/

aabb_t aabb_union(aabb_t a, aabb_t b);
flt_t aabb_area(aabb_t a);