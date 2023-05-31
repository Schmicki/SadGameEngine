#pragma once

#include "platform.h"
#include "math.h"
#include "containers.h"

#if defined(OS_WINDOWS) /* OS_WINDOWS */

#define GLEW_STATIC 1

#include "GL/glew.h"

/*************************************************************************************************/

typedef struct vertex_t
{
	vec3_t position;
	vec4_t color;
	vec3_t normal;
	vec2_t uv;
} vertex_t;

/*************************************************************************************************/

typedef struct mesh_data_t
{
	u32_t vertex_count;
	u32_t index_count;
	vec3_t* positions;
	vec4_t* colors;
	vec3_t* normals;
	vec2_t* uvs;
	u32_t* indices;
} mesh_data_t;

/*************************************************************************************************/

typedef struct gl_mesh_t
{
	u32_t vao;
	u32_t vbo;
	u32_t ibo;
	u32_t vertex_count;
	u32_t index_count;
} gl_mesh_t;

/*************************************************************************************************/

typedef struct gl_lod_t
{
	gl_mesh_t* sections;
	u8_t* material_indices;
	u8_t section_count;
} gl_lod_t;

/*************************************************************************************************/

typedef struct gl_model_t
{
	aabb_t bounds;
	gl_lod_t* lods;
	flt_t* lod_squared_distances;
	uptr_t* materials;
	u8_t lod_count;
	u8_t material_count;
} gl_model_t;

/*************************************************************************************************/

typedef struct gl_scene_tree_t
{
	vector_t data;
} gl_scene_tree_t;

/*************************************************************************************************/

typedef struct gl_scene_t
{
	vector_t models;
	vector_t directional_lights;
	vector_t point_lights;
	vector_t spot_lights;
	vector_t trees;
} gl_scene_t;

/*************************************************************************************************/

typedef HGLRC gl_context_t;

/*************************************************************************************************/

mesh_data_t mesh_plane();

mesh_data_t mesh_cube(u32_t subdivisions);

mesh_data_t mesh_sphere(u32_t subdivisions, flt_t radius);

void_t mesh_free(mesh_data_t* mesh);

gl_mesh_t gl_mesh_new(mesh_data_t* data);

void_t gl_mesh_free(gl_mesh_t* mesh);

void_t gl_draw_mesh(gl_mesh_t* mesh);

/*************************************************************************************************/

gl_context_t gl_context_new(window_t* window);

void gl_context_free(window_t* window, gl_context_t context);

u32_t gl_shader_compile(u32_t type, const char_t* code);

u32_t gl_pipeline_new(const char_t* vertex_shader, const char_t* fragment_shader);

void gl_pipeline_free(u32_t pipeline);

u32_t gl_pipeline_from_files(const char_t* vertex_shader, const char_t* fragment_shader);

u32_t gl_image_from_file(const char_t* path);

u32_t gl_cubemap_from_files(const char_t* left, const char_t* right, const char_t* top, const char_t* bottom, const char_t* front, const char_t* back);

void gl_error_loop();

/*************************************************************************************************/

uptr_t gl_model_load(const char_t* path);

void_t gl_model_free(const char_t* path);

uptr_t gl_material_load(const char_t* path);

void_t gl_material_free(const char_t* path);

uptr_t gl_texture2d_load(const char_t* path);

void_t gl_texture2d_free(const char_t* path);

uptr_t gl_scene_new();

void_t gl_scene_free(uptr_t scene);

uptr_t gl_scene_add_model(uptr_t scene, uptr_t model, uptr_t* material_overrides, u8_t material_count, transform_t transform);

void_t gl_scene_update_model(uptr_t scene, uptr_t instance, uptr_t model, uptr_t* material_overrides, u8_t material_count, transform_t transform);

void_t gl_scene_remove_model(uptr_t scene, uptr_t instance);

uptr_t gl_scene_new_point_light(uptr_t scene, vec3_t position, vec3_t color, flt_t radius);

void_t gl_scene_update_point_light(uptr_t scene, uptr_t instance, vec3_t position, vec3_t color, flt_t radius);

void_t gl_scene_remove_point_light(uptr_t scene, uptr_t instance);

uptr_t gl_scene_add_spot_light(uptr_t scene, vec3_t position, vec3_t forward, vec3_t color, flt_t angle);

void_t gl_scene_update_spot_light(uptr_t scene, uptr_t instance, vec3_t position, vec3_t forward, vec3_t color, flt_t angle);

void_t gl_scene_remove_spot_light(uptr_t scene, uptr_t instance);

uptr_t gl_scene_add_directional_light(uptr_t scene, vec3_t forward, vec3_t color);

void_t gl_scene_update_directional_light(uptr_t scene, uptr_t instance, vec3_t forward, vec3_t color);

void_t gl_scene_remove_directional_light(uptr_t scene, uptr_t instance);

#endif /* OS_WINDOWS */