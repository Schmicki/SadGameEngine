#pragma once

#include "platform.h"

/*************************************************************************************************/

/* 12 - 16 bytes. */
typedef struct vector_t
{
	void_t* data;
	u32_t len;
	u32_t cap;
} vector_t;

/*************************************************************************************************/

/* 12 - 16 bytes. */
typedef struct string_t
{
	char_t* data;
	u32_t len;
	u32_t cap;
} string_t;

/*************************************************************************************************/

/* 16 - 24 bytes. */
typedef struct flat_map_t
{
	void_t* buckets;
	u32_t len;
	u32_t cap;
	cmpfunc_t cmp;
} flat_map_t;

/*************************************************************************************************/

/* 24 - 40 bytes. */
typedef struct flat_hashmap_t
{
	void_t* buckets;
	u8_t* info;
	u32_t len;
	u32_t cap;
	hashfunc_t hash;
	cmpfunc_t cmp;
} flat_hashmap_t;

/*************************************************************************************************/

/* The elem size should always be >= sizeof(uptr_t). 16 - 24 bytes. */
typedef struct pool_t
{
	void_t** data;
	u32_t len;
	u32_t cap;
	u32_t bcap;
} pool_t;

/*************************************************************************************************/

u32_t container_compute_capacity(u32_t len);

/*************************************************************************************************/

/* 'size' is the size of a single elem in bytes. */
vector_t vector_new(u32_t size, u32_t len);

void_t vector_free(vector_t* vec);

/* 'size' is the size of a single elem in bytes. */
void_t vector_reserve(vector_t* vec, u32_t size, u32_t len);

/* Trim vector to lowest fitting capacity.
 * 'size' is the size of a single elem in bytes. */
void_t vector_trim(vector_t* vec, u32_t size);

/* 'size' is the size of a single elem in bytes. */
void_t* vector_get(vector_t* vec, u32_t size, u32_t idx);

/* 'size' is the size of a single elem in bytes. */
void_t vector_insert(vector_t* vec, u32_t size, void_t* elem, u32_t idx);

/* 'size' is the size of a single elem in bytes. */
u32_t vector_push(vector_t* vec, u32_t size, void_t* elem);

/* 'size' is the size of a single elem in bytes. */
void_t vector_erase(vector_t* vec, u32_t size, u32_t idx);

u32_t vector_find(vector_t* vec, u32_t size, void_t* elem, cmpfunc_t cmp);

/*************************************************************************************************/

string_t string_new(u32_t len);

void_t string_free(string_t* str);

void_t string_reserve(string_t* str, u32_t len);

/* Trim string to lowest fitting capacity. */
void_t string_trim(string_t* str);

char_t* string_get(string_t* str, u32_t idx);

void_t string_insert(string_t* str, char_t* seq, u32_t len, u32_t idx);

void_t string_append(string_t* str, char_t* seq, u32_t len);

void_t string_erase(string_t* str, u32_t idx, u32_t len);

u16_t* string_to_utf16(string_t* str, u32_t* out_len);

u32_t* string_to_utf32(string_t* str, u32_t* out_len);

string_t string_from_utf16(u16_t* str, u32_t* out_len);

string_t string_from_utf32(u32_t* str, u32_t* out_len);

i32_t string_cmp(string_t* a, string_t* b);

u32_t string_hash32(const char_t* string);

u32_t utf8_symbol_size(const char_t c);

u32_t utf8_len(const char_t* str);

u32_t utf8_len_utf16(const u16_t* str);

u32_t utf8_len_utf32(const u32_t* str);

u32_t utf8_encode(char_t* str, u32_t symbol);

u32_t utf8_decode(const char_t* str, u32_t* out_symbol);

u16_t* utf8_to_utf16(char_t* str, u32_t* out_len);

u32_t* utf8_to_utf32(char_t* str, u32_t* out_len);

u32_t utf16_symbol_size(const u16_t c);

u32_t utf16_len(const u16_t* str);

u32_t utf16_len_utf8(const char_t* str);

u32_t utf16_encode(u16_t* str, u32_t symbol);

u32_t utf16_decode(const u16_t* str, u32_t* out_symbol);

u32_t utf32_len_utf8(const char_t* str);

/*************************************************************************************************/

/* 'size' is the size of a single bucket in bytes. */
flat_map_t flat_map_new(u32_t size, u32_t len, cmpfunc_t cmp);

void_t flat_map_free(flat_map_t* map);

/* 'size' is the size of a single elem in bytes. */
void_t flat_map_reserve(flat_map_t* map, u32_t size, u32_t len);

/* Trim vector to lowest fitting capacity.
 * 'size' is the size of a single elem in bytes. */
void_t flat_map_trim(flat_map_t* map, u32_t size);

/* 'size' is the size of a single elem in bytes. */
void_t* flat_map_get(flat_map_t* map, u32_t size, void_t* bucket);

/* 'size' is the size of a single elem in bytes. */
void_t* flat_map_push(flat_map_t* map, u32_t size, void_t* bucket);

/* 'size' is the size of a single elem in bytes.
 * 'out_bucket' is used to store the data of a bucket if found. */
u8_t flat_map_pop(flat_map_t* map, u32_t size, void_t* bucket, void_t* out_bucket);

/*************************************************************************************************/

/* 'size' is the size of a single bucket in bytes. */
flat_hashmap_t flat_hashmap_new(u32_t size, u32_t len, hashfunc_t hash, cmpfunc_t cmp);

void_t flat_hashmap_free(flat_hashmap_t* map);

/* 'size' is the size of a single elem in bytes. */
void_t flat_hashmap_reserve(flat_hashmap_t* map, u32_t size, u32_t len);

/* Trim vector to lowest fitting capacity.
 * 'size' is the size of a single elem in bytes. */
void_t flat_hashmap_trim(flat_hashmap_t* map, u32_t size);

/* 'size' is the size of a single elem in bytes. */
void_t* flat_hashmap_get(flat_hashmap_t* map, u32_t size, void_t* bucket);

/* 'size' is the size of a single elem in bytes. */
void_t* flat_hashmap_push(flat_hashmap_t* map, u32_t size, void_t* bucket);

/* 'size' is the size of a single elem in bytes.
 * 'out_bucket' is used to store the data of a bucket if found. */
u8_t flat_hashmap_pop(flat_hashmap_t* map, u32_t size, void_t* bucket, void_t* out_bucket);

/*************************************************************************************************/

/* 'size' is the size of a single elem in bytes.
 * 'bcap' is the number of elements a single block/allocation can hold. */
pool_t pool_new(u32_t size, u32_t len, u32_t bcap);

void_t pool_free(pool_t* pool);

/* 'size' is the size of a single elem in bytes. */
void_t pool_reserve(pool_t* pool, u32_t size, u32_t len);

/* 'size' is the size of a single elem in bytes. */
void_t* pool_get(pool_t* pool, u32_t size, u32_t idx);

/* 'size' is the size of a single elem in bytes. */
u32_t pool_push(pool_t* pool, u32_t size, void_t* elem);

/* 'size' is the size of a single elem in bytes. */
void_t pool_erase(pool_t* pool, u32_t size, u32_t idx);
