#pragma once

#include "platform.h"
#include "containers.h"
#include "math.h"
#include "opengl.h"

/*************************************************************************************************/

#define SPHERE_COUNT 100
#define SPHERE_RANGE 20

typedef struct camera_t
{
    vec3_t location;
    vec3_t rotation;
    vec3_t scale;
} camera_t;

#if defined(OS_WINDOWS) /* OS_WINDOWS */

typedef struct scene_light_t
{
    camera_t camera;
    transform_t spheres[SPHERE_COUNT];
    transform_t light;
    gl_mesh_t sphere_mesh;
    gl_mesh_t plane_mesh;
    gl_mesh_t cube_mesh;
    u32_t texture0, texture1, skybox, sphere_shader, light_shader, effect_shader, skybox_shader,
        framebuffer, color_attachment, depth_attachment, viewport[4];
} scene_light_t;

typedef struct scene_depth_t
{
    camera_t camera;
    transform_t spheres[SPHERE_COUNT];
    gl_mesh_t sphere_mesh;
    u32_t shader;
} scene_depth_t;

/*************************************************************************************************/

u8_t scene_light_new(scene_light_t* scene);

void_t scene_light_free(scene_light_t* scene);

void_t scene_light_render(scene_light_t* scene, flt_t time, flt_t delta_time);

/*************************************************************************************************/

u8_t scene_depth_new(scene_depth_t* scene);

void_t scene_depth_free(scene_depth_t* scene);

void_t scene_depth_render(scene_depth_t* scene, flt_t time, flt_t delta_time);

#endif /* OS_HAS_WINDOW */