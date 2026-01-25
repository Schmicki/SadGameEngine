#pragma once

#include "platform.h"
#include "containers.h"

#define ecs_get_id(entity) (entity & 0xFFFFFF)
#define ecs_set_id(entity, id) ((entity & ~0xFFFFFF) | (id & 0xFFFFFF))

#define ecs_get_gen(entity) (entity >> 24)
#define ecs_set_gen(entity, gen) ((entity & 0xFFFFFF) | (gen << 24))

typedef u32_t ecs_entity_t;/*

typedef struct ecs_chunk_t {

} ecs_chunk_t;

typedef struct ecs_table_t {

} ecs_table_t;

typedef struct ecs_registry_t {
	vector_t entities;
	vector_t tables;
	flat_hashmap_t components;
} ecs_registry_t;*/
