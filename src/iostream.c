#include "iostream.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

u8_t* load_file(const char* file, u32_t oversize, u32_t* out_len)
{
    FILE* _file;
    fpos_t file_end;
    u8_t* data;

    _file = fopen(file, "rb");
    fseek(_file, 0, SEEK_END);
    fgetpos(_file, &file_end);
    rewind(_file);

    data = malloc(file_end + (fpos_t)oversize);
    fread(data, 1, file_end, _file);

    fclose(_file);

    if (out_len != NULL)
        *out_len = (u32_t)file_end;

    return data;
}

u8_t* load_image_from_file(const char* file, u32_t* out_x, u32_t* out_y)
{
    u8_t* image;
    u8_t* pixels;
    i32_t channels;
    u32_t size;

    image = load_file(file, 0, &size);
    pixels = stbi_load_from_memory(image, size, (int*)out_x, (int*)out_y, (int*)&channels, 4);
    free(image);

    return pixels;
}