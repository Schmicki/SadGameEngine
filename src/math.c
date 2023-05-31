#include <math.h>
#include "math.h"

/*************************************************************************************************/

vec2_t vec2_set(flt_t x, flt_t y)
{
    vec2_t vec = { x, y };
    return vec;
}

vec2_t vec2_add(vec2_t a, vec2_t b)
{
    vec2_t tmp = {(a.x + b.x), (a.y + b.y)};
    return tmp;
}

vec2_t vec2_sub(vec2_t a, vec2_t b)
{
    vec2_t tmp =  { (a.x - b.x), (a.y - b.y) };
    return tmp;
}

vec2_t vec2_mul(vec2_t a, flt_t v)
{
    vec2_t tmp =  { (a.x * v), (a.y * v) };
    return tmp;
}

vec2_t vec2_div(vec2_t a, flt_t v)
{
    vec2_t tmp =  { (a.x / v), (a.y / v) };
    return tmp;
}

flt_t vec2_dot(vec2_t a, vec2_t b)
{
    return (a.x * b.x) + (a.y * b.y);
}

flt_t vec2_len(vec2_t a)
{
    return flt_sqrt(vec2_dot(a, a));
}

vec2_t vec2_unit(vec2_t a)
{
    return vec2_div(a, vec2_len(a));
}

vec2_t vec2_lerp(vec2_t from, vec2_t to, flt_t alpha)
{
    return vec2_add(from, vec2_mul(vec2_sub(to, from), alpha));
}

i32_t vec2_cmp(vec2_t a, vec2_t b)
{
    if (a.x != b.x) return a.x > b.x ? 1 : -1;
    if (a.y != b.y) return a.y > b.y ? 1 : -1;
    return 0;
}

/*************************************************************************************************/

vec3_t vec3_set(flt_t x, flt_t y, flt_t z)
{
    vec3_t vec = { x, y, z };
    return vec;
}

vec3_t vec3_add(vec3_t a, vec3_t b)
{
    vec3_t tmp =  { (a.x + b.x), (a.y + b.y), (a.z + b.z) };
    return tmp;
}

vec3_t vec3_sub(vec3_t a, vec3_t b)
{
    vec3_t tmp =  { (a.x - b.x), (a.y - b.y), (a.z - b.z) };
    return tmp;
}

vec3_t vec3_mul(vec3_t a, flt_t v)
{
    vec3_t tmp =  { (a.x * v), (a.y * v), (a.z * v) };
    return tmp;
}

vec3_t vec3_div(vec3_t a, flt_t v)
{
    vec3_t tmp =  { (a.x / v), (a.y / v), (a.z / v) };
    return tmp;
}

vec3_t vec3_cross(vec3_t a, vec3_t b)
{
    vec3_t tmp =  {
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x),
    };
    return tmp;
}

flt_t vec3_dot(vec3_t a, vec3_t b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

flt_t vec3_len(vec3_t a)
{
    return flt_sqrt(vec3_dot(a, a));
}

vec3_t vec3_unit(vec3_t a)
{
    flt_t len;

    len = vec3_len(a);

    return len > (flt_t)0 ? vec3_div(a, len) : a;
}

vec3_t vec3_lerp(vec3_t from, vec3_t to, flt_t alpha)
{
    return vec3_add(from, vec3_mul(vec3_sub(to, from), alpha));
}

vec3_t vec3_rotate(vec3_t a, quat_t r)
{
    return vec3_transform(a, mat4_rotation(r));
}

vec3_t vec3_transform(vec3_t a, mat4_t t)
{
    vec3_t tmp =  {
        a.x * t.m[0] + a.y * t.m[1]
        + a.z * t.m[2] + t.m[3],
        a.x * t.m[4] + a.y * t.m[5]
        + a.z * t.m[6] + t.m[7],
        a.x * t.m[8] + a.y * t.m[9]
        + a.z * t.m[10] + t.m[11]
    };
    return tmp;
}

i32_t vec3_cmp(vec3_t a, vec3_t b)
{
    if (a.x != b.x) return a.x > b.x ? 1 : -1;
    if (a.y != b.y) return a.y > b.y ? 1 : -1;
    if (a.z != b.z) return a.z > b.z ? 1 : -1;
    return 0;
}

/*************************************************************************************************/

vec4_t vec4_set(flt_t x, flt_t y, flt_t z, flt_t w)
{
    vec4_t vec = { x, y, z, w };
    return vec;
}

vec4_t vec4_add(vec4_t a, vec4_t b)
{
    vec4_t tmp =  { (a.x + b.x), (a.y + b.y), (a.z + b.z), (a.w + b.w) };
    return tmp;
}

vec4_t vec4_sub(vec4_t a, vec4_t b)
{
    vec4_t tmp =  { (a.x - b.x), (a.y - b.y), (a.z - b.z), (a.w - b.w) };
    return tmp;
}

vec4_t vec4_mul(vec4_t a, flt_t v)
{
    vec4_t tmp =  { (a.x * v), (a.y * v), (a.z * v), (a.w * v) };
    return tmp;
}

vec4_t vec4_div(vec4_t a, flt_t v)
{
    vec4_t tmp =  { (a.x / v), (a.y / v), (a.z / v), (a.w / v) };
    return tmp;
}

flt_t vec4_dot(vec4_t a, vec4_t b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

flt_t vec4_len(vec4_t a)
{
    return flt_sqrt(vec4_dot(a, a));
}

vec4_t vec4_unit(vec4_t a)
{
    return vec4_div(a, vec4_len(a));
}

vec4_t vec4_lerp(vec4_t from, vec4_t to, flt_t alpha)
{
    return vec4_add(from, vec4_mul(vec4_sub(to, from), alpha));
}

vec4_t vec4_transform(vec4_t a, mat4_t t)
{
    vec4_t tmp = {
        a.x * t.m[0] + a.y * t.m[1]
        + a.z * t.m[2] + a.w * t.m[3],
        a.x * t.m[4] + a.y * t.m[5]
        + a.z * t.m[6] + a.w * t.m[7],
        a.x * t.m[8] + a.y * t.m[9]
        + a.z * t.m[10] + a.w * t.m[11],
        a.x * t.m[12] + a.y * t.m[13]
        + a.z * t.m[14] + a.w * t.m[15]
    };
    return tmp;
}

i32_t vec4_cmp(vec4_t a, vec4_t b)
{
    if (a.x != b.x) return a.x > b.x ? 1 : -1;
    if (a.y != b.y) return a.y > b.y ? 1 : -1;
    if (a.z != b.z) return a.z > b.z ? 1 : -1;
    if (a.w != b.w) return a.w > b.w ? 1 : -1;
    return 0;
}

/*************************************************************************************************/

quat_t quat_euler_angles(vec3_t angles)
{
    flt_t cx, sx, cy, sy, cz, sz;
    cx = flt_cos(flt_dtor(angles.x * 0.5f)),
    sx = flt_sin(flt_dtor(angles.x * 0.5f)),
    cy = flt_cos(flt_dtor(angles.y * 0.5f)),
    sy = flt_sin(flt_dtor(angles.y * 0.5f)),
    cz = flt_cos(flt_dtor(angles.z * 0.5f)),
    sz = flt_sin(flt_dtor(angles.z * 0.5f));

    quat_t tmp =  {
        cx* sy* sz - sx * cy * cz,
        -cx * sy * cz - sx * cy * sz,
        cx* cy* sz - sx * sy * cz,
        cx* cy* cz + sx * sy * sz
    };
    return tmp;
}

quat_t quat_axis_angle(vec3_t axis, flt_t angle)
{
    flt_t sin, cos;
    cos = flt_cos(flt_dtor(angle * 0.5f)),
    sin = flt_sin(flt_dtor(angle * 0.5f));
    axis = vec3_mul(axis, sin);
    quat_t tmp = { axis.x, axis.y, axis.z, cos };
    return tmp;
}

quat_t quat_add(quat_t a, quat_t b)
{
    quat_t tmp =  { (a.x + b.x), (a.y + b.y), (a.z + b.z), (a.w + b.w) };
    return tmp;
}

quat_t quat_sub(quat_t a, quat_t b)
{
    quat_t tmp =  { (a.x - b.x), (a.y - b.y), (a.z - b.z), (a.w - b.w) };
    return tmp;
}

quat_t quat_mul(quat_t a, flt_t v)
{
    quat_t tmp =  { (a.x * v), (a.y * v), (a.z * v), (a.w * v) };
    return tmp;
}

quat_t quat_div(quat_t a, flt_t v)
{
    quat_t tmp =  { (a.x / v), (a.y / v), (a.z / v), (a.w / v) };
    return tmp;
}

flt_t quat_dot(quat_t a, quat_t b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

flt_t quat_len(quat_t a)
{
    return flt_sqrt(quat_dot(a, a));
}

quat_t quat_unit(quat_t a)
{
    return quat_div(a, quat_len(a));
}

quat_t quat_conj(quat_t a)
{
    quat_t tmp =  { -a.x, -a.y, -a.z, a.w };
    return tmp;
}

quat_t quat_inv(quat_t a)
{
    return quat_div(quat_conj(a), quat_dot(a, a));
}

quat_t quat_lerp(quat_t from, quat_t to, flt_t alpha)
{
    return quat_add(from, quat_mul(quat_sub(to, from), alpha));
}

quat_t quat_nlerp(quat_t from, quat_t to, flt_t alpha)
{
    return quat_unit(quat_lerp(from, to, alpha));
}

quat_t quat_slerp(quat_t from, quat_t to, flt_t alpha)
{
    flt_t dot, angle;
    dot = quat_dot(from, to);
    angle = flt_acos(dot);
    from = dot < 0 ? from : quat_mul(from, (flt_t)-1.0);
    from = quat_mul(from, flt_sin(((flt_t)1.0 - alpha) * angle));
    from = quat_add(from, quat_mul(to, flt_sin(alpha * angle)));
    return quat_div(from, flt_sin(angle));
}

quat_t quat_slerpl(quat_t from, quat_t to, flt_t alpha)
{
    flt_t dot, angle;
    dot = quat_dot(from, to);
    angle = flt_acos(dot);
    from = dot < 0 ? quat_mul(from, (flt_t)-1.0) : from;
    from = quat_mul(from, flt_sin(((flt_t)1.0 - alpha) * angle));
    from = quat_add(from, quat_mul(to, flt_sin(alpha * angle)));
    return quat_div(from, flt_sin(angle));
}

quat_t quat_rotate(quat_t a, quat_t b)
{
    quat_t tmp = {
        (a.x * b.w) + (a.w * b.x) + (a.y * b.z) - (a.z * b.y),
        (a.y * b.w) + (a.w * b.y) + (a.z * b.x) - (a.x * b.z),
        (a.z * b.w) + (a.w * b.z) + (a.x * b.y) - (a.y * b.x),
        (a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z),
    };
    return tmp;
}

/*************************************************************************************************/

mat3_t mat3_add(mat3_t a, mat3_t b)
{
    mat3_t tmp =  {
        a.m[0] + b.m[0], a.m[1] + b.m[1], a.m[2] + b.m[2],
        a.m[3] + b.m[3], a.m[4] + b.m[4], a.m[5] + b.m[5],
        a.m[6] + b.m[6], a.m[7] + b.m[7], a.m[8] + b.m[8]
    };
    return tmp;
}

mat3_t mat3_sub(mat3_t a, mat3_t b)
{
    mat3_t tmp =  {
        a.m[0] - b.m[0], a.m[1] - b.m[1], a.m[2] - b.m[2],
        a.m[3] - b.m[3], a.m[4] - b.m[4], a.m[5] - b.m[5],
        a.m[6] - b.m[6], a.m[7] - b.m[7], a.m[8] - b.m[8]
    };
    return tmp;
}

mat3_t mat3_mul(mat3_t a, mat3_t b)
{
    mat3_t tmp =  {
        (a.m[0] * b.m[0]) + (a.m[1] * b.m[3]) + (a.m[2] * b.m[6]),
        (a.m[0] * b.m[1]) + (a.m[1] * b.m[4]) + (a.m[2] * b.m[7]),
        (a.m[0] * b.m[2]) + (a.m[1] * b.m[5]) + (a.m[2] * b.m[8]),

        (a.m[3] * b.m[0]) + (a.m[4] * b.m[3]) + (a.m[5] * b.m[6]),
        (a.m[3] * b.m[1]) + (a.m[4] * b.m[4]) + (a.m[5] * b.m[7]),
        (a.m[3] * b.m[2]) + (a.m[4] * b.m[5]) + (a.m[5] * b.m[8]),

        (a.m[6] * b.m[0]) + (a.m[7] * b.m[3]) + (a.m[8] * b.m[6]),
        (a.m[6] * b.m[1]) + (a.m[7] * b.m[4]) + (a.m[8] * b.m[7]),
        (a.m[6] * b.m[2]) + (a.m[7] * b.m[5]) + (a.m[8] * b.m[8]),
    };
    return tmp;
}

/*************************************************************************************************/

mat4_t mat4_translation(vec3_t t)
{
    mat4_t tmp =  {
        1.0f, 0.0f, 0.0f, t.x,
        0.0f, 1.0f, 0.0f, t.y,
        0.0f, 0.0f, 1.0f, t.z,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return tmp;
}

mat4_t mat4_rotation(quat_t r)
{
    mat4_t tmp =  {
        (flt_t)1.0 - ((flt_t)2.0 * r.y * r.y) - ((flt_t)2.0 * r.z * r.z),
        ((flt_t)2.0 * r.x * r.y) - ((flt_t)2.0 * r.w * r.z),
        ((flt_t)2.0 * r.x * r.z) + ((flt_t)2.0 * r.w * r.y),
        (flt_t)0.0,
        ((flt_t)2.0 * r.x * r.y) + ((flt_t)2.0 * r.w * r.z),
        (flt_t)1.0 - ((flt_t)2.0 * r.x * r.x) - ((flt_t)2.0 * r.z * r.z),
        ((flt_t)2.0 * r.y * r.z) - ((flt_t)2.0 * r.w * r.x),
        (flt_t)0.0,
        ((flt_t)2.0 * r.x * r.z) - ((flt_t)2.0 * r.w * r.y),
        ((flt_t)2.0 * r.y * r.z) + ((flt_t)2.0 * r.w * r.x),
        (flt_t)1.0 - ((flt_t)2.0 * r.x * r.x) - ((flt_t)2.0 * r.y * r.y),
        (flt_t)0.0,
        (flt_t)0.0, (flt_t)0.0 ,(flt_t)0.0,
        (flt_t)1.0
    };
    return tmp;
}

mat4_t mat4_scale(vec3_t s)
{
    mat4_t tmp =  {
        s.x, 0.0f, 0.0f, 0.0f,
        0.0f, s.y, 0.0f, 0.0f,
        0.0f, 0.0f, s.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return tmp;
}

mat4_t mat4_model(transform_t transform)
{
    return mat4_mul(mat4_mul(
        mat4_translation(transform.location),
        mat4_rotation(transform.rotation)),
        mat4_scale(transform.scale));
}

mat4_t mat4_view(vec3_t location, vec3_t rotation)
{
    return mat4_mul(
        mat4_rotation(quat_inv(quat_euler_angles(rotation))),
        mat4_translation(vec3_mul(location, (flt_t)-1)));
}

mat4_t mat4_mvp(mat4_t model, mat4_t view, mat4_t projection)
{
    return mat4_mul(projection, mat4_mul(view, model));
}

mat4_t mat4_perspective_vk(flt_t fov, flt_t ratio, flt_t near, flt_t far)
{
    flt_t fov_div_two_tan, a, b, c, d;
    fov_div_two_tan = flt_tan(flt_dtor(fov / 2.0f));
    a = 1.0f / (ratio * fov_div_two_tan);
    b = 1.0f / fov_div_two_tan;
    c, d;

    if (far > flt_abs(near))
    {
        if (near > 0.0f)
        {
            c = far / (far - near);
            d = (-near * far) / (far - near);
        }
        else
        {
            /* Reverse z-plane. */
            c = near / (far + near);
            d = (-near * far) / (far + near);
        }
    }
    else
    {
        /* Infinite far plane. */
        if (near > 0.0f)
        {
            c = 1.0f;
            d = -near;
        }
        else
        {
            /* Reverse z-plane. */
            c = 0.0f;
            d = -near;
        }
    }

    mat4_t tmp =  {
           a, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f,    b, 0.0f,
        0.0f,    c, 0.0f,    d,
        0.0f, 1.0f, 0.0f, 0.0f
    };
    return tmp;
}

mat4_t mat4_perspective_gl(flt_t fov, flt_t ratio, flt_t near, flt_t far)
{
    flt_t fov_div_two_tan, a, b, c, d;
    fov_div_two_tan = flt_tan(flt_dtor(fov / 2.0f));
    a = 1.0f / (ratio * fov_div_two_tan);
    b = 1.0f / fov_div_two_tan;
    c, d;

    if (far > flt_abs(near))
    {
        if (near > 0.0f)
        {
            c = (far + near) / (far - near);
            d = (-2.0f * near * far) / (far - near);
        }
        else
        {
            /* Reverse z-plane. */
            c = -(far - near) / (far + near);
            d = (2.0f * -near * far) / (far + near);
        }
    }
    else
    {
        /* Infinite far plane. */
        if (near > 0.0f)
        {
            c = 1.0f;
            d = -2.0f * near;
        }
        else
        {
            /* Reverse z-plane. */
            c = 0.0f;
            d = -near;
        }
    }

    mat4_t tmp = {
           a, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f,    b, 0.0f,
        0.0f,    c, 0.0f,    d,
        0.0f, 1.0f, 0.0f, 0.0f
    };
    return tmp;
}

mat4_t _mat4_perspective_gu(flt_t fov, flt_t ratio, flt_t near, flt_t far)
{
    flt_t fov_div_two_tan, a, b, c, d;
    fov_div_two_tan = flt_tan(flt_dtor(fov / 2.0f));
    a = 1.0f / (ratio * fov_div_two_tan);
    b = 1.0f / fov_div_two_tan;
    c, d;

    if (far > flt_abs(near))
    {
        if (near > 0.0f)
        {
            c = near / (far - near);
            d = (-near * far) / (far - near);
        }
        else
        {
            /* Reverse z-plane. */
            c = -far / (far + near);
            d = (-near * far) / (far + near);
        }
    }
    else
    {
        /* Infinite far plane. */
        if (near > 0.0f)
        {
            c = 0.0f;
            d = -near;
        }
        else
        {
            /* Reverse z-plane. */
            c = -1.0f;
            d = -near;
        }
    }

    mat4_t tmp = {
           a, 0.0f, 0.0f, 0.0f,
        0.0f,    b, 0.0f, 0.0f,
        0.0f, 0.0f,    c,    d,
        0.0f, 0.0f, 1.0f, 0.0f
    };
    return tmp;
}

mat4_t mat4_perspective_gu(flt_t fov, flt_t ratio, flt_t near, flt_t far)
{
    flt_t fov_div_two_tan, a, b, c, d;
    fov_div_two_tan = flt_tan(flt_dtor(fov / 2.0f));
    a = 1.0f / (ratio * fov_div_two_tan);
    b = 1.0f / fov_div_two_tan;
    c, d;

    if (far > flt_abs(near))
    {
        if (near > 0.0f)
        {
            c = (far + near) / (far - near);
            d = (-2.0f * near * far) / (far - near);
        }
        else
        {
            /* Reverse z-plane. */
            c = -far / (far + near);
            d = (-near * far) / (far + near);
        }
    }
    else
    {
        /* Infinite far plane. */
        if (near > 0.0f)
        {
            c = 0.0f;
            d = -near;
        }
        else
        {
            /* Reverse z-plane. */
            c = -1.0f;
            d = -near;
        }
    }

    mat4_t tmp = {
           a, 0.0f, 0.0f, 0.0f,
        0.0f,    b, 0.0f, 0.0f,
        0.0f, 0.0f,    c,    d,
        0.0f, 0.0f, 1.0f, 0.0f
    };
    return tmp;
}

mat4_t mat4_add(mat4_t a, mat4_t b)
{
    mat4_t tmp =  {
        a.m[ 0] + b.m[ 0], a.m[ 1] + b.m[ 1], a.m[ 2] + b.m[ 2], a.m[ 3] + b.m[ 3],
        a.m[ 4] + b.m[ 4], a.m[ 5] + b.m[ 5], a.m[ 6] + b.m[ 6], a.m[ 7] + b.m[ 7],
        a.m[ 8] + b.m[ 8], a.m[ 9] + b.m[ 9], a.m[10] + b.m[10], a.m[11] + b.m[11],
        a.m[12] + b.m[12], a.m[13] + b.m[13], a.m[14] + b.m[14], a.m[15] + b.m[15]
    };
    return tmp;
}

mat4_t mat4_sub(mat4_t a, mat4_t b)
{
    mat4_t tmp =  {
        a.m[ 0] - b.m[ 0], a.m[ 1] - b.m[ 1], a.m[ 2] - b.m[ 2], a.m[ 3] - b.m[ 3],
        a.m[ 4] - b.m[ 4], a.m[ 5] - b.m[ 5], a.m[ 6] - b.m[ 6], a.m[ 7] - b.m[ 7],
        a.m[ 8] - b.m[ 8], a.m[ 9] - b.m[ 9], a.m[10] - b.m[10], a.m[11] - b.m[11],
        a.m[12] - b.m[12], a.m[13] - b.m[13], a.m[14] - b.m[14], a.m[15] - b.m[15]
    };
    return tmp;
}

mat4_t mat4_mul(mat4_t a, mat4_t b)
{
    mat4_t tmp =  {
        a.m[ 0] * b.m[ 0] + a.m[ 1] * b.m[ 4] + a.m[ 2] * b.m[ 8] + a.m[ 3] * b.m[12],
        a.m[ 0] * b.m[ 1] + a.m[ 1] * b.m[ 5] + a.m[ 2] * b.m[ 9] + a.m[ 3] * b.m[13],
        a.m[ 0] * b.m[ 2] + a.m[ 1] * b.m[ 6] + a.m[ 2] * b.m[10] + a.m[ 3] * b.m[14],
        a.m[ 0] * b.m[ 3] + a.m[ 1] * b.m[ 7] + a.m[ 2] * b.m[11] + a.m[ 3] * b.m[15],

        a.m[ 4] * b.m[ 0] + a.m[ 5] * b.m[ 4] + a.m[ 6] * b.m[ 8] + a.m[ 7] * b.m[12],
        a.m[ 4] * b.m[ 1] + a.m[ 5] * b.m[ 5] + a.m[ 6] * b.m[ 9] + a.m[ 7] * b.m[13],
        a.m[ 4] * b.m[ 2] + a.m[ 5] * b.m[ 6] + a.m[ 6] * b.m[10] + a.m[ 7] * b.m[14],
        a.m[ 4] * b.m[ 3] + a.m[ 5] * b.m[ 7] + a.m[ 6] * b.m[11] + a.m[ 7] * b.m[15],

        a.m[ 8] * b.m[ 0] + a.m[ 9] * b.m[ 4] + a.m[10] * b.m[ 8] + a.m[11] * b.m[12],
        a.m[ 8] * b.m[ 1] + a.m[ 9] * b.m[ 5] + a.m[10] * b.m[ 9] + a.m[11] * b.m[13],
        a.m[ 8] * b.m[ 2] + a.m[ 9] * b.m[ 6] + a.m[10] * b.m[10] + a.m[11] * b.m[14],
        a.m[ 8] * b.m[ 3] + a.m[ 9] * b.m[ 7] + a.m[10] * b.m[11] + a.m[11] * b.m[15],

        a.m[12] * b.m[ 0] + a.m[13] * b.m[ 4] + a.m[14] * b.m[ 8] + a.m[15] * b.m[12],
        a.m[12] * b.m[ 1] + a.m[13] * b.m[ 5] + a.m[14] * b.m[ 9] + a.m[15] * b.m[13],
        a.m[12] * b.m[ 2] + a.m[13] * b.m[ 6] + a.m[14] * b.m[10] + a.m[15] * b.m[14],
        a.m[12] * b.m[ 3] + a.m[13] * b.m[ 7] + a.m[14] * b.m[11] + a.m[15] * b.m[15],
    };
    return tmp;
}

mat4_t mat4_transpose(mat4_t a)
{
    mat4_t tmp = {
        a.m[0], a.m[4], a.m[8], a.m[12],
        a.m[1], a.m[5], a.m[8], a.m[13],
        a.m[2], a.m[6], a.m[9], a.m[14],
        a.m[3], a.m[4], a.m[10], a.m[15]
    };

    return tmp;
}

/*************************************************************************************************/

#if defined(FLT_64)

flt_t flt_abs(flt_t v)
{
    return fabs(v);
}

flt_t flt_min(flt_t a, flt_t b)
{
    return fmin(a, b);
}

flt_t flt_max(flt_t a, flt_t b)
{
    return fmax(a, b);
}

flt_t flt_trunc(flt_t v)
{
    return trunc(v);
}

flt_t flt_round(flt_t v)
{
    return round(v);
}

flt_t flt_mod(flt_t v, flt_t mod)
{
    return fmod(v, mod);
}

flt_t flt_clamp(flt_t v, flt_t min, flt_t max)
{
    return fmax(min, fminf(max, v));
}

flt_t flt_sin(flt_t v)
{
    return sin(v);
}

flt_t flt_asin(flt_t v)
{
    return asin(v);
}

flt_t flt_cos(flt_t v)
{
    return cos(v);
}

flt_t flt_acos(flt_t v)
{
    return acos(v);
}

flt_t flt_tan(flt_t v)
{
    return tan(v);
}

flt_t flt_atan(flt_t v)
{
    return atan(v);
}

flt_t flt_pow(flt_t v, flt_t exp)
{
    return pow(v, exp);
}

flt_t flt_log2(flt_t v)
{
    return log2(v);
}

flt_t flt_sqrt(flt_t v)
{
    return sqrt(v);
}

#else

flt_t flt_abs(flt_t v)
{
    return fabsf(v);
}

flt_t flt_min(flt_t a, flt_t b)
{
    return fminf(a, b);
}

flt_t flt_max(flt_t a, flt_t b)
{
    return fmaxf(a, b);
}

flt_t flt_trunc(flt_t v)
{
    return truncf(v);
}

flt_t flt_round(flt_t v)
{
    return roundf(v);
}

flt_t flt_mod(flt_t v, flt_t mod)
{
    return fmodf(v, mod);
}

flt_t flt_clamp(flt_t v, flt_t min, flt_t max)
{
    return fmaxf(min, fminf(max, v));
}

flt_t flt_sin(flt_t v)
{
    return sinf(v);
}

flt_t flt_asin(flt_t v)
{
    return asinf(v);
}

flt_t flt_cos(flt_t v)
{
    return cosf(v);
}

flt_t flt_acos(flt_t v)
{
    return acosf(v);
}

flt_t flt_tan(flt_t v)
{
    return tanf(v);
}

flt_t flt_atan(flt_t v)
{
    return atanf(v);
}

flt_t flt_pow(flt_t v, flt_t exp)
{
    return powf(v, exp);
}

flt_t flt_log2(flt_t v)
{
    return log2f(v);
}

flt_t flt_sqrt(flt_t v)
{
    return sqrtf(v);
}

#endif