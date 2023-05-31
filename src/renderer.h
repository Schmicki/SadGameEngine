#pragma once

#include "platform.h"
#include "containers.h"
#include "math.h"

/*************************************************************************************************/

typedef struct render_interface_t render_interface_t;

/*************************************************************************************************/

struct render_interface_t
{
	uptr_t (*model_load)(const char_t* path);
	void_t (*model_free)(const char_t* path);
	uptr_t (*material_load)(const char_t* path);
	void_t (*material_free)(const char_t* path);
	uptr_t (*texture2d_load)(const char_t* path);
	void_t (*texture2d_free)(const char_t* path);
	uptr_t (*scene_new)();
	void_t (*scene_free)(uptr_t scene);
	uptr_t (*scene_add_model)(uptr_t scene, uptr_t model, uptr_t* material_overrides, transform_t transform);
	void_t (*scene_update_model)(uptr_t scene, uptr_t instance, uptr_t model, uptr_t* material_overrides, transform_t transform);
	void_t (*scene_remove_model)(uptr_t scene, uptr_t instance);
	uptr_t (*scene_new_point_light)(uptr_t scene, vec3_t position, vec3_t color, flt_t radius);
	void_t (*scene_update_point_light)(uptr_t scene, uptr_t instance, vec3_t position, vec3_t color, flt_t radius);
	void_t (*scene_remove_point_light)(uptr_t scene, uptr_t instance);
	uptr_t (*scene_add_spot_light)(uptr_t scene, vec3_t position, vec3_t forward, vec3_t color, flt_t angle);
	void_t (*scene_update_spot_light)(uptr_t scene, uptr_t instance, vec3_t position, vec3_t forward, vec3_t color, flt_t angle);
	void_t (*scene_remove_spot_light)(uptr_t scene, uptr_t instance);
	uptr_t (*scene_add_directional_light)(uptr_t scene, vec3_t forward, vec3_t color);
	void_t (*scene_update_directional_light)(uptr_t scene, uptr_t instance, vec3_t forward, vec3_t color);
	void_t (*scene_remove_directional_light)(uptr_t scene, uptr_t instance);
};

/*************************************************************************************************/

uptr_t model_load(const char_t* path);

void_t model_free(const char_t* path);

uptr_t material_load(const char_t* path);

void_t material_free(const char_t* path);

uptr_t texture2d_load(const char_t* path);

void_t texture2d_free(const char_t* path);

uptr_t scene_new();

void_t scene_free(uptr_t scene);

uptr_t scene_add_model(uptr_t scene, uptr_t model, uptr_t* material_overrides, u8_t material_count, transform_t transform);

void_t scene_update_model(uptr_t scene, uptr_t instance, uptr_t model, uptr_t* material_overrides, u8_t material_count, transform_t transform);

void_t scene_remove_model(uptr_t scene, uptr_t instance);

uptr_t scene_new_point_light(uptr_t scene, vec3_t position, vec3_t color, flt_t radius);

void_t scene_update_point_light(uptr_t scene, uptr_t instance, vec3_t position, vec3_t color, flt_t radius);

void_t scene_remove_point_light(uptr_t scene, uptr_t instance);

uptr_t scene_add_spot_light(uptr_t scene, vec3_t position, vec3_t forward, vec3_t color, flt_t angle);

void_t scene_update_spot_light(uptr_t scene, uptr_t instance, vec3_t position, vec3_t forward, vec3_t color, flt_t angle);

void_t scene_remove_spot_light(uptr_t scene, uptr_t instance);

uptr_t scene_add_directional_light(uptr_t scene, vec3_t forward, vec3_t color);

void_t scene_update_directional_light(uptr_t scene, uptr_t instance, vec3_t forward, vec3_t color);

void_t scene_remove_directional_light(uptr_t scene, uptr_t instance);