#pragma once

#include "platform.h"
#include "containers.h"

typedef u32_t ecs_entity_t;

#define ecs_get_id(entity) (entity & 0xFFFFFF)
#define ecs_set_id(entity, id) ((entity & ~0xFFFFFF) | (id & 0xFFFFFF))

#define ecs_get_gen(entity) (entity >> 24)
#define ecs_set_gen(entity, gen) ((entity & 0xFFFFFF) | (gen << 24))