#include "containers.h"

/*************************************************************************************************/

u32_t container_compute_capacity(u32_t len)
{
	return (len < 8) ? 8 : 1 << (u32_highest_bit(len - 1) + 1);
}

/*************************************************************************************************/

vector_t vector_new(u32_t size, u32_t len)
{
    vector_t array = {NULL, 0, 0};
	vector_reserve(&array, size, len);
    return array;
}

void_t vector_free(vector_t* vec)
{
	free(vec->data);
}

void_t vector_reserve(vector_t* vec, u32_t size, u32_t len)
{
    if (vec->cap < len)
    {
        void_t* new_data;

        len = container_compute_capacity(len);
        new_data = malloc((uptr_t)size * (uptr_t)len);
        vec->cap = len;

        memcpy(new_data, vec->data, (uptr_t)vec->len * (uptr_t)size);
        vector_free(vec);
        vec->data = new_data;
    }
}

void_t vector_trim(vector_t* vec, u32_t size)
{
    if ((vec->cap / 4) > vec->len)
    {
        vec->cap = container_compute_capacity(vec->len * 2);
        vec->data = realloc(vec->data, (uptr_t)vec->cap * (uptr_t)size);
    }
}

void_t* vector_get(vector_t* vec, u32_t size, u32_t idx)
{
	return (void_t*)((uptr_t*)vec->data + ((uptr_t)size * (uptr_t)idx));
}

void_t vector_insert(vector_t* vec, u32_t size, void_t* elem, u32_t idx)
{
	void_t* dst, *src;

	vector_reserve(vec, size, vec->len + 1);
	src = (void_t*)((uptr_t)vec->data + ((uptr_t)idx * (uptr_t)size));
	dst = (void_t*)((uptr_t)src + (uptr_t)size);
	memmove(dst, src, (uptr_t)(vec->len - idx) * (uptr_t)size);
	memcpy(src, elem, size);
	vec->len++;
}

u32_t vector_push(vector_t* vec, u32_t size, void_t* elem)
{
	vector_insert(vec, size, elem, vec->len);
	return vec->len - 1;
}

void_t vector_erase(vector_t* vec, u32_t size, u32_t idx)
{
    void_t* src, *dst;
    uptr_t sz;

    if (idx >= vec->len)
        return;

    vec->len--;

    sz = (uptr_t)idx * (uptr_t)size;
    src = (u8_t*)vec->data + sz + (uptr_t)size;
    dst = (u8_t*)vec->data + sz;
    sz = (uptr_t)(vec->len - idx) * (uptr_t)size;

    memmove(dst, src, sz);
    vector_trim(vec, size);
}

u32_t vector_find(vector_t* vec, u32_t size, void_t* elem, cmpfunc_t cmp)
{
	u32_t i;
	void_t* e, *end;

	e = vec->data;
	end = (void_t*)((uptr_t)e + ((uptr_t)vec->len * (uptr_t)size));

	for (i = 0; e < end; e = (void_t*)((uptr_t)e + (uptr_t)size), i++)
	{
		if (cmp(elem, e) == 0)
			return i;
	}

	return U32_MAX;
}

/*************************************************************************************************/

string_t string_new(u32_t len)
{
	string_t str = { NULL, 0, 0 };
	string_reserve(&str, len);
	return str;
}

void_t string_free(string_t* str)
{
	free(str->data);
}

void_t string_reserve(string_t* str, u32_t len)
{
	if (str->cap <= len)
	{
		char_t* new_data;

		str->cap = container_compute_capacity(len + 1);
		new_data = (char_t*)malloc(str->cap);
		memcpy(new_data, str->data, str->len);
		new_data[str->len] = 0;
		string_free(str);
		str->data = new_data;
	}
}

void_t string_trim(string_t* str)
{
	if ((str->cap / 4) > str->len)
	{
		str->cap = container_compute_capacity(str->len * 2);
		str->data = realloc(str->data, (uptr_t)str->cap);
	}
}

char_t* string_get(string_t* str, u32_t idx)
{
	return str->data + idx;
}

void_t string_insert(string_t* str, char_t* seq, u32_t len, u32_t idx)
{
	string_reserve(str, str->len + len);
	memmove(str->data + idx + len, str->data + idx, str->len - idx);
	memcpy(str->data + idx, seq, len);
	str->len += len;
	str->data[str->len] = 0;
}

void_t string_append(string_t* str, char_t* seq, u32_t len)
{
	string_insert(str, seq, len, str->len);
}

void_t string_erase(string_t* str, u32_t idx, u32_t len)
{
	if ((idx + len) > str->len)
		return;

	memmove(str->data + idx, str->data + idx + len, str->len - idx - len);
	str->len -= len;
	str->data[str->len] = 0;
	string_trim(str);
}

u16_t* string_to_utf16(string_t* str, u32_t* out_len)
{
	u32_t x, y, symbol, size;
	u16_t* string;

	size = utf16_len_utf8(str->data);
	string = malloc(sizeof(u16_t) * (size + 1));
	string[size] = 0;
	out_len == NULL ? ((u32_t)0) : (*out_len = size);

	for (x = 0, y = 0; str->data[x] != 0;)
		x += utf8_decode(str->data + x, &symbol),
		y += utf16_encode(string + y, symbol);

	return string;
}

u32_t* string_to_utf32(string_t* str, u32_t* out_len)
{
	u32_t x, y, symbol, size;
	u32_t* string;

	size = utf32_len_utf8(str->data);
	string = malloc(sizeof(u32_t) * (size + 1));
	string[size] = 0;
	out_len == NULL ? ((u32_t)0) : (*out_len = size);

	for (x = 0, y = 0; str->data[x] != 0;)
		x += utf8_decode(str->data + x, &symbol),
		string[y++] = symbol;

	return string;
}

string_t string_from_utf16(u16_t* str, u32_t* out_len)
{
	u32_t x, y, symbol, size;
	string_t string;

	size = utf8_len_utf16(str);
	string = string_new(size);
	string.data[size] = 0;
	out_len == NULL ? ((u32_t)0) : (*out_len = size);

	for (x = 0, y = 0; str[x] != 0;)
		x += utf16_decode(str + x, &symbol),
		y += utf8_encode(string.data + y, symbol);

	return string;
}

string_t string_from_utf32(u32_t* str, u32_t* out_len)
{
	u32_t x, y, symbol, size;
	string_t string;

	size = utf8_len_utf32(str);
	string = string_new(size);
	string.data[size] = 0;
	out_len == NULL ? ((u32_t)0) : (*out_len = size);

	for (x = 0, y = 0; str[x] != 0;)
		symbol = str[x++], y += utf8_encode(string.data + y, symbol);

	return string;
}

i32_t string_cmp(string_t* a, string_t* b)
{
	return strcmp(a->data, b->data);
}

u32_t string_hash32(const char_t* string)
{
	u32_t multiplier = 31;
	u32_t i, m, hash = 0;

	for (i = 0, m = 1; string[i] != 0; m *= multiplier, i++)
	{
		hash += string[i] * m;
	}

	return hash;
}

/* UTF-8
 * 01111111                             7-bit ASCII characters
 * 110xxxxx 10xxxxxx                    2-byte sequence 11-bit characters
 * 1110xxxx 10xxxxxx 10xxxxxx           3-byte sequence 16-bit characters
 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx  4-byte sequence 21-bit characters
 *
 * ASCII: 0 - 127
 *
 * Start: 192u - 253u		||	-64 - -3
 * Following: 128u - 191u	||	-128 - -65
 *
 * Start 2: 192u - 223u		||	-64 - -33
 * Start 3: 224u - 239u		||	-32 - -17
 * Start 4: 240u - 247u		||	-16 - -9
 * Start 5: 248u - 251u		||	-8 - -5
 * Start 6: 252u - 253u		||	-4 - -3
 *
 * UTF-16 Little Endian & Big Endian (standard x86 is little endian, the byte order is mirrored
 * on big endian)
 * xxxxxxxx xxxxxxxx                    16-bit Unicode characters
 * 110110xx xxxxxxxx                    High
 * 110111xx xxxxxxxx                    Low
 * 110110xx xxxxxxxx 110110xx xxxxxxxx  4-byte sequence 20-bit charcaters
 * Everything between
 * (11011000 00000000 - 11011011 11111111) (0xD800 - 0xDBFF)
 * (11011100 00000000 - 11011111 11111111) (0xDC00 - 0xDFFF)
 * is reserved space in unicode so you can identify UTF-16 "Surrogate Pairs". */

u32_t utf8_symbol_size(const char_t c)
{
	return 1 + ((u8_t)c > 0xBF) + ((u8_t)c > 0xDF) + ((u8_t)c > 0xEF);
}

u32_t utf8_len(const char_t* str)
{
	u32_t len;

	if (str == NULL)
		return 0;

	for (len = 0; str[len] != 0; len += utf8_symbol_size(str[len]));
	return len;
}

u32_t utf8_len_utf16(const u16_t* str)
{
	u32_t i, len;

	if (str == NULL)
		return 0;

	for (i = 0, len = 0; str[i] != 0; utf16_symbol_size(str[i]) == 2 ?
		(len += 4, i += 2) : (len += 1 + (str[i] > 0x7F) + (str[i] > 0x7FF), i++));
	return len;
}

u32_t utf8_len_utf32(const u32_t* str)
{
	u32_t i, len;
	for (i = 0, len = 0; str[i] != 0; len += 1 + (str[i] > 0x7F) + (str[i] > 0x7FF) + (str[i] > 0xFFFF), i++);
	return len;
}

u32_t utf8_encode(char_t* str, u32_t symbol)
{
	if (symbol < 0x80)
	{
		str[0] = symbol;
		return 1;
	}
	else if (symbol < 0x800)
	{
		str[0] = 0xC0 | (char_t)(symbol >> 6);
		str[1] = 0x80 | (char_t)(symbol & 0x3F);
		return 2;
	}
	else if (symbol < 0x10000)
	{
		str[0] = 0xE0 | (char_t)(symbol >> 12);
		str[1] = 0x80 | (char_t)(symbol >> 6 & 0x3F);
		str[2] = 0x80 | (char_t)(symbol & 0x3F);
		return 3;
	}
	else
	{
		str[0] = 0xF0 | (char_t)(symbol >> 18);
		str[1] = 0x80 | (char_t)(symbol >> 12) & 0x3F;
		str[2] = 0x80 | (char_t)(symbol >> 6) & 0x3F;
		str[3] = 0x80 | (char_t)(symbol & 0x3F);
		return 4;
	}
}

u32_t utf8_decode(const char_t* str, u32_t* out_symbol)
{
	switch (utf8_symbol_size(str[0]))
	{
	default:
		return 0;
	case 0:
		*out_symbol = 0;
		return 0;
	case 1:
		*out_symbol = str[0];
		return 1;
	case 2:
		*out_symbol = ((0x1F & str[0]) << 6) | (0x1F & str[1]);
		return 2;
	case 3:
		*out_symbol = ((0xF & str[0]) << 12) | ((0x1F & str[1]) << 6) | (0x1F & str[2]);
		return 3;
	case 4:
		*out_symbol = ((0x7 & str[0]) << 18) | ((0x1F & str[1]) << 12) | ((0x1F & str[2]) << 6) | (0x1F & str[3]);
		return 4;
	}
}

u16_t* utf8_to_utf16(char_t* str, u32_t* out_len)
{
	u32_t x, y, symbol, size;
	u16_t* string;

	size = utf16_len_utf8(str);
	string = malloc(sizeof(u16_t) * (size + 1));
	string[size] = 0;
	out_len == NULL ? ((u32_t)0) : (*out_len = size);

	for (x = 0, y = 0; str[x] != 0;)
		x += utf8_decode(str + x, &symbol),
		y += utf16_encode(string + y, symbol);

	return string;
}

u32_t* utf8_to_utf32(char_t* str, u32_t* out_len)
{
	u32_t x, y, symbol, size;
	u32_t* string;

	size = utf32_len_utf8(str);
	string = malloc(sizeof(u32_t) * (size + 1));
	string[size] = 0;
	out_len == NULL ? ((u32_t)0) : (*out_len = size);

	for (x = 0, y = 0; str[x] != 0;)
		x += utf8_decode(str + x, &symbol),
		string[y++] = symbol;

	return string;
}

u32_t utf16_symbol_size(const u16_t c)
{
	return 1 + ((c > 0xD7FF) & (c < 0xE000));
}

u32_t utf16_len(const u16_t* str)
{
	u32_t len;

	if (str == NULL)
		return 0;

	for (len = 0; str[len] != 0; len += utf16_symbol_size(str[len]));
	return len;
}

u32_t utf16_len_utf8(const char_t* str)
{
	u32_t i, len;

	if (str == NULL)
		return 0;

	for (i = 0, len = 0; str[i] != 0;)
	{
		u32_t size;

		size = utf8_symbol_size(str[i]);
		len += 1 + (size > 3);
		i += size;
	}

	return len;
}

u32_t utf16_encode(u16_t* str, u32_t symbol)
{
	if (symbol < 0x10000)
	{
		str[0] = (u16_t)symbol;
		return 1;
	}
	else
	{
		symbol -= 0x10000;
		str[0] = 0xD800 | ((symbol >> 10) & 0x3FF);
		str[1] = 0xDC00 | (symbol & 0x3FF);
		return 2;
	}
}

u32_t utf16_decode(const u16_t* str, u32_t* out_symbol)
{
	u32_t size;

	size = utf16_symbol_size(str[0]);
	size == 1 ? (*out_symbol = str[0]) :
		(*out_symbol = ((((u32_t)str[0] & 0x3FF) << 10) | ((u32_t)str[1] & 0x3FF)) + 0x10000);
	return size;
}

u32_t utf32_len_utf8(const char_t* str)
{
	u32_t i, len;

	if (str == NULL)
		return 0;

	for (i = 0, len = 0; str[i] != 0; i += utf8_symbol_size(str[len]), i++);
	return len;
}

/*************************************************************************************************/

flat_map_t flat_map_new(u32_t size, u32_t len, cmpfunc_t cmp)
{
	flat_map_t map = { NULL, 0, 0, cmp };
	flat_map_reserve(&map, size, len);
	return map;
}

void_t flat_map_free(flat_map_t* map)
{
	free(map->buckets);
}

void_t flat_map_reserve(flat_map_t* map, u32_t size, u32_t len)
{
	if (map->cap < len)
	{
		void_t* new_data;

		len = container_compute_capacity(len);
		new_data = malloc((uptr_t)size * (uptr_t)len);
		map->cap = len;

		memcpy(new_data, map->buckets, (uptr_t)map->len * (uptr_t)size);
		flat_map_free(map);
		map->buckets = new_data;
	}
}

void_t flat_map_trim(flat_map_t* map, u32_t size)
{
	if ((map->cap / 4) > map->len)
	{
		map->cap = container_compute_capacity(map->len * 2);
		map->buckets = realloc(map->buckets, (uptr_t)map->cap * (uptr_t)size);
	}
}

void_t* flat_map_get_index(flat_map_t* map, u32_t size, void_t* bucket, u32_t* out_index)
{
	if (map->len == 0)
	{
		*out_index = 0;
		return NULL;
	}

	u32_t low, mid, high;
	i32_t result;

	low = 0; high = map->len - 1;

	while (low <= high)
	{
		void_t* _bucket;

		mid = low + ((high - low) / 2);
		_bucket = (u8_t*)map->buckets + ((uptr_t)mid * (uptr_t)size);
		result = map->cmp(bucket, _bucket);

		if (result > 0)
		{
			low = mid + 1;
		}
		else if (result < 0)
		{
			if (mid != 0)
			{
				high = mid - 1;
				continue;
			}

			*out_index = 0;
			return NULL;
		}
		else
		{
			*out_index = mid;
			return _bucket;
		}
	}

	*out_index = low;
	return NULL;
}

void_t* flat_map_get(flat_map_t* map, u32_t size, void_t* bucket)
{
	u32_t index;
	return flat_map_get_index(map, size, bucket, &index);
}

void_t* flat_map_push(flat_map_t* map, u32_t size, void_t* bucket)
{
	u32_t index;
	void_t* _bucket;

	_bucket = flat_map_get_index(map, size, bucket, &index);

	if (_bucket != NULL)
		return _bucket;

	vector_insert((vector_t*)map, size, bucket, index);
	return NULL;
}

u8_t flat_map_pop(flat_map_t* map, u32_t size, void_t* bucket, void_t* out_bucket)
{
	u32_t index;
	void_t* _bucket;

	_bucket = flat_map_get_index(map, size, bucket, &index);

	if (_bucket != NULL)
	{
		memcpy(out_bucket, _bucket, size);
		vector_erase((vector_t*)map, size, index);
		return TRUE;
	}

	return FALSE;
}

/*************************************************************************************************/

flat_hashmap_t flat_hashmap_new(u32_t size, u32_t len, hashfunc_t hash, cmpfunc_t cmp)
{
	u32_t sz, cap;
	flat_hashmap_t map;

	cap = container_compute_capacity(len);
	sz = (cap * size) + size;

	map.buckets = malloc(sz + cap);
	map.info = (u8_t*)map.buckets + sz;
	map.cap = cap;
	map.len = 0;
	map.hash = hash;
	map.cmp = cmp;

	memset(map.info, U8_MAX, map.cap);
	return map;
}

void_t flat_hashmap_free(flat_hashmap_t* map)
{
	free(map->buckets);
}

void_t flat_hashmap_reserve(flat_hashmap_t* map, u32_t size, u32_t len)
{
	if (len > (map->cap - (map->cap / 4)))
	{
		flat_hashmap_t new_map;
		u32_t i;

		new_map = flat_hashmap_new(size, len * 2, map->hash, map->cmp);

		for (i = 0; i < map->cap; i++)
		{
			if (map->info[i] != U8_MAX)
			{
				void_t* _bucket = (void_t*)((uptr_t)map->buckets + ((uptr_t)size * (uptr_t)i));
				flat_hashmap_push(&new_map, size, _bucket);
			}
		}

		flat_hashmap_free(map);
		*map = new_map;
	}
}

void_t flat_hashmap_trim(flat_hashmap_t* map, u32_t size)
{
	if ((map->cap - (map->cap - (map->cap / 4))) > map->len)
	{
		flat_hashmap_t new_map;
		u32_t i;

		new_map = flat_hashmap_new(size, map->len, map->hash, map->cmp);

		for (i = 0; i < map->cap; i++)
		{
			if (map->info[i] != U8_MAX)
			{
				void_t* _bucket = (void_t*)((uptr_t)map->buckets + ((uptr_t)size * (uptr_t)i));
				flat_hashmap_push(&new_map, size, _bucket);
			}
		}

		flat_hashmap_free(map);
		*map = new_map;
	}
}

void_t* flat_hashmap_get_index(flat_hashmap_t* map, u32_t size, u32_t hash, void_t* bucket, u32_t* out_index)
{
	u32_t mask, idx, distance;

	mask = map->cap - 1;
	idx = hash & mask;
	distance = 0;

	for (;; idx = (idx + 1) & mask, distance++)
	{
		void_t* _bucket;
		u32_t _distance;

		_bucket = (void_t*)((uptr_t)map->buckets + ((uptr_t)idx * (uptr_t)size));
		_distance = map->info[idx];

		if ((_distance == U8_MAX) | (distance > _distance))
		{
			*out_index = idx;
			return NULL;
		}
		else if (map->cmp(bucket, _bucket) == 0)
		{
			*out_index = idx;
			return _bucket;
		}
	}
}

void_t* flat_hashmap_get(flat_hashmap_t* map, u32_t size, void_t* bucket)
{
	u32_t idx;
	return flat_hashmap_get_index(map, size, map->hash(bucket), bucket, &idx);
}

void_t* flat_hashmap_push(flat_hashmap_t* map, u32_t size, void_t* bucket)
{
	u32_t mask, hash, idx, distance;
	void_t* _bucket;

	flat_hashmap_reserve(map, size, map->len + 1);

	hash = map->hash(bucket);
	_bucket = flat_hashmap_get_index(map, size, hash, bucket, &idx);

	if (_bucket != NULL)
		return _bucket;

	mask = map->cap - 1;
	distance = ((map->cap + idx) - (hash & mask)) & mask;

	for (;; idx = (idx + 1) & mask, distance++)
	{
		u32_t _distance;

		_bucket = (void_t*)((uptr_t)map->buckets + ((uptr_t)idx * (uptr_t)size));
		_distance = map->info[idx];

		if (_distance == U8_MAX)
		{
			memcpy(_bucket, bucket, size);
			map->info[idx] = distance;
			map->len++;
			return NULL;
		}
		else if (distance > _distance)
		{
			void_t* tmp_one, * tmp_two;

			tmp_one = (void_t*)((uptr_t)map->buckets + ((uptr_t)map->cap * (uptr_t)size));
			tmp_two = (void_t*)((uptr_t)tmp_one + (uptr_t)size);

			memcpy(tmp_one, _bucket, size);
			memcpy(_bucket, bucket, size);
			memcpy(tmp_two, tmp_one, size);

			bucket = tmp_two;
			map->info[idx] = distance;
			distance = _distance;
		}
	}
}

u8_t flat_hashmap_pop(flat_hashmap_t* map, u32_t size, void_t* bucket, void_t* out_key)
{
	u32_t mask, hash, idx, next;

	hash = map->hash(bucket);

	if (flat_hashmap_get_index(map, size, hash, bucket, &idx) == NULL)
		return FALSE;

	memcpy(out_key, (void_t*)((uptr_t)map->buckets + ((uptr_t)idx * (uptr_t)size)), size);

	mask = map->cap - 1;

	for (next = (idx + 1) & mask;; idx = next, next = (next + 1) & mask)
	{
		void_t* _bucket;
		void_t* next_bucket;
		u32_t next_distance;

		next_distance = map->info[next];

		if ((next_distance == U8_MAX) | (next_distance == 0))
		{
			map->info[idx] = U8_MAX;
			map->len--;
			break;
		}

		_bucket = (void_t*)((uptr_t)map->buckets + ((uptr_t)idx * (uptr_t)size));
		next_bucket = (void_t*)((uptr_t)_bucket + (uptr_t)size);

		memcpy(_bucket, next_bucket, size);
		map->info[idx] = next_distance - 1;
	}

	flat_hashmap_trim(map, size);

	return TRUE;
}