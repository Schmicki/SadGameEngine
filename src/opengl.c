#include "opengl.h"

#if defined(OS_WINDOWS) /* OS_WINDOWS */

mesh_data_t _mesh_allocate(u32_t vertex_count, u32_t index_count)
{
    mesh_data_t mesh;
    u32_t vbo_size, ibo_size;

    vbo_size = vertex_count * sizeof(vertex_t);
    ibo_size = index_count * sizeof(u32_t);

    mesh.vertex_count = vertex_count;
    mesh.index_count = index_count;
    mesh.positions = malloc(vbo_size + ibo_size);
    mesh.colors = (vec4_t*)(mesh.positions + vertex_count);
    mesh.normals = (vec3_t*)(mesh.colors + vertex_count);
    mesh.uvs = (vec2_t*)(mesh.normals + vertex_count);
    mesh.indices = (u32_t*)(mesh.uvs + vertex_count);

    return mesh;
}

mesh_data_t mesh_plane()
{
    mesh_data_t mesh;

    mesh = _mesh_allocate(4, 6);
    
    mesh.positions[0] = vec3_set(0.0f, 0.0f, 0.0f);
    mesh.positions[1] = vec3_set(1.0f, 0.0f, 0.0f);
    mesh.positions[2] = vec3_set(0.0f, 1.0f, 0.0f);
    mesh.positions[3] = vec3_set(1.0f, 1.0f, 0.0f);

    mesh.uvs[0] = vec2_set(0.0f, 0.0f);
    mesh.uvs[1] = vec2_set(1.0f, 0.0f);
    mesh.uvs[2] = vec2_set(0.0f, 1.0f);
    mesh.uvs[3] = vec2_set(1.0f, 1.0f);

    mesh.indices[0] = 0;
    mesh.indices[1] = 2;
    mesh.indices[2] = 3;
    mesh.indices[3] = 0;
    mesh.indices[4] = 3;
    mesh.indices[5] = 1;

    return mesh;
}

mesh_data_t mesh_cube(u32_t subdivisions)
{

    mesh_data_t mesh;
    u32_t flen, vlen, v;

    vlen = 2 + subdivisions;
    flen = vlen - 1;
    v = 0;

    mesh = _mesh_allocate(vlen * vlen * 6, flen * flen * 6 * 6);

    for (u32_t i = 0; i < vlen; i++)
    {
        for (u32_t j = 0; j < vlen; j++, v++)
        {
            mesh.positions[v] = vec3_set((flt_t)j / flen - 0.5f, 0 - 0.5f, (flt_t)i / flen - 0.5f);
            mesh.uvs[v] = vec2_set((flt_t)j / flen, 1.0f - (flt_t)i / flen);
        }
    }

    for (u32_t i = 0; i < vlen; i++)
    {
        for (u32_t j = 0; j < vlen; j++, v++)
        {
            mesh.positions[v] = vec3_set(1.0f - (flt_t)j / flen - 0.5f, (flt_t)flen / flen - 0.5f, (flt_t)i / flen - 0.5f);
            mesh.uvs[v] = vec2_set((flt_t)j / flen, 1.0f - (flt_t)i / flen);
        }
    }

    for (u32_t i = 0; i < vlen; i++)
    {
        for (u32_t j = 0; j < vlen; j++, v++)
        {
            mesh.positions[v] = vec3_set((flt_t)j / flen - 0.5f, (flt_t)i / flen - 0.5f, (flt_t)flen / flen - 0.5f);
            mesh.uvs[v] = vec2_set((flt_t)j / flen, 1.0f - (flt_t)i / flen);
        }
    }

    for (u32_t i = 0; i < vlen; i++)
    {
        for (u32_t j = 0; j < vlen; j++, v++)
        {
            mesh.positions[v] = vec3_set(1.0f - (flt_t)j / flen - 0.5f, (flt_t)i / flen - 0.5f, 0 - 0.5f);
            mesh.uvs[v] = vec2_set((flt_t)j / flen, 1.0f - (flt_t)i / flen);
        }
    }

    for (u32_t i = 0; i < vlen; i++)
    {
        for (u32_t j = 0; j < vlen; j++, v++)
        {
            mesh.positions[v] = vec3_set((flt_t)flen / flen - 0.5f, (flt_t)j / flen - 0.5f, (flt_t)i / flen - 0.5f);
            mesh.uvs[v] = vec2_set((flt_t)j / flen, 1.0f - (flt_t)i / flen);
        }
    }

    for (u32_t i = 0; i < vlen; i++)
    {
        for (u32_t j = 0; j < vlen; j++, v++)
        {
            mesh.positions[v] = vec3_set(0 - 0.5f, 1.0f - (flt_t)j / flen - 0.5f, (flt_t)i / flen - 0.5f);
            mesh.uvs[v] = vec2_set((flt_t)j / flen, 1.0f - (flt_t)i / flen);
        }
    }

    for (u32_t i = 0, v = 0, t = 0; i < flen * 6; i++, v++)
    {
        if (i != 0 && i % flen == 0)
            v += vlen;

        for (u32_t j = 0; j < flen; j++, t += 6, v++)
        {
            mesh.indices[t] = v;
            mesh.indices[t + 1] = v + vlen;
            mesh.indices[t + 2] = v + vlen + 1;
            mesh.indices[t + 3] = v + vlen + 1;
            mesh.indices[t + 4] = v + 1;
            mesh.indices[t + 5] = v;
        }
    }

    return mesh;
}

mesh_data_t mesh_sphere(u32_t subdivisions, flt_t radius)
{
    mesh_data_t mesh;
    u32_t i;
    vec3_t center;

    mesh = mesh_cube(subdivisions);
    center = vec3_set(0, 0, 0);

    for (i = 0; i < mesh.vertex_count; i++)
    {
        mesh.normals[i] = vec3_unit(vec3_sub(mesh.positions[i], center));
        mesh.positions[i] = vec3_mul(mesh.normals[i], radius);
    }

    return mesh;
}

void_t mesh_free(mesh_data_t* mesh)
{
    free(mesh->positions);
}

gl_mesh_t gl_mesh_new(mesh_data_t* data)
{
    gl_mesh_t mesh;
    u32_t vbo_size;

    mesh.vao = 0;
    mesh.vbo = 0;
    mesh.ibo = 0;
    mesh.vertex_count = data->vertex_count;
    mesh.index_count = data->index_count;
    
    vbo_size = mesh.vertex_count * sizeof(vertex_t);

    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, vbo_size, data->positions, GL_STATIC_DRAW);

    /* enable positions */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3_t), 0);

    /* enable colors */
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4_t), (void_t*)((u8_t*)data->colors
        - (u8_t*)data->positions));

    /* enable normals */
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3_t), (void_t*)((u8_t*)data->normals
        - (u8_t*)data->positions));

    /* enable uvs */
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vec2_t), (void_t*)((u8_t*)data->uvs
        - (u8_t*)data->positions));

    if (mesh.index_count > 0)
    {
        glGenBuffers(1, &mesh.ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32_t) * mesh.index_count, data->indices, GL_STATIC_DRAW);
    }

    return mesh;
}

void_t gl_mesh_free(gl_mesh_t* mesh)
{
    glDeleteVertexArrays(1, &mesh->vao);
    glDeleteBuffers(1, &mesh->vbo);
    if (mesh->index_count > 0)
        glDeleteBuffers(1, &mesh->ibo);

    mesh->vao = 0;
    mesh->vbo = 0;
    mesh->ibo = 0;
    mesh->vertex_count = 0;
    mesh->index_count = 0;
}

void_t gl_draw_mesh(gl_mesh_t* mesh)
{
    glBindVertexArray(mesh->vao);

    if (mesh->index_count == 0)
    {
        glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
        glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, NULL);
    }
}

gl_context_t gl_context_new(window_t* window)
{
    PIXELFORMATDESCRIPTOR format_descriptor;
    i32_t format_id;
    HDC dc;
    HGLRC context;

    memset(&format_descriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
    format_descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    format_descriptor.nVersion = 1;
    format_descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
    format_descriptor.iPixelType = PFD_TYPE_RGBA;
    format_descriptor.cColorBits = 32;
    format_descriptor.cDepthBits = 24;
    format_descriptor.cStencilBits = 8;
    format_descriptor.iLayerType = PFD_MAIN_PLANE;

    dc = GetDC(window->handle);
    format_id = ChoosePixelFormat(dc, &format_descriptor);
    SetPixelFormat(dc, format_id, &format_descriptor);
    context = wglCreateContext(dc);
    wglMakeCurrent(dc, context);

    return context;
}

void gl_context_free(window_t* window, gl_context_t context)
{
    HDC dc;

    dc = GetDC(window->handle);
    wglMakeCurrent(dc, NULL);
    wglDeleteContext(context);
}

u32_t gl_shader_compile(u32_t type, const char_t* code)
{
    u32_t id;
    i32_t result;

    id = glCreateShader(type);
    glShaderSource(id, 1, &code, NULL);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        i32_t errmsglen;
        char* msg;

        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errmsglen);
        msg = malloc(errmsglen);
        glGetShaderInfoLog(id, errmsglen, &errmsglen, msg);
        printf("ERROR! %s\n", msg);
        free(msg);
        glDeleteShader(id);

        return 0;
    }

    return id;
}

u32_t gl_pipeline_new(const char_t* vertex_shader, const char_t* fragment_shader)
{
    u32_t vertex_shader_id, fragment_shader_id, pipeline_id;

    vertex_shader_id = gl_shader_compile(GL_VERTEX_SHADER, vertex_shader);
    fragment_shader_id = gl_shader_compile(GL_FRAGMENT_SHADER, fragment_shader);

    pipeline_id = glCreateProgram();
    glAttachShader(pipeline_id, vertex_shader_id);
    glAttachShader(pipeline_id, fragment_shader_id);
    glLinkProgram(pipeline_id);
    glValidateProgram(pipeline_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return pipeline_id;
}

void gl_pipeline_free(u32_t pipeline)
{
    glDeleteProgram(pipeline);
}

u32_t gl_pipeline_from_files(const char_t* vertex_shader, const char_t* fragment_shader)
{
    char_t* vertex_shader_code, *fragment_shader_code;
    u32_t file_size, pipeline_id;

    /* load shaders */
    vertex_shader_code = load_file(vertex_shader, 1, &file_size);
    vertex_shader_code[file_size] = 0;
    //printf("%s%s\n\n", "vertex shader:\n", vertex_shader_code);

    fragment_shader_code = load_file(fragment_shader, 1, &file_size);
    fragment_shader_code[file_size] = 0;
    //printf("%s%s\n\n", "fragment shader:\n", fragment_shader_code);

    /* create pipeline */
    pipeline_id = gl_pipeline_new(vertex_shader_code, fragment_shader_code);

    free(vertex_shader_code);
    free(fragment_shader_code);

    return pipeline_id;
}

u32_t gl_image_from_file(const char_t* path)
{
    void_t* data;
    u32_t width, height, id;

    data = load_image_from_file(path, &width, &height);

    if (data == NULL)
    {
        printf("ERROR!%s%s\n", "Failed to load texture: ", path);
        return 0;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    free(data);

    return id;
}

u32_t gl_cubemap_from_files(const char_t* left, const char_t* right, const char_t* top, const char_t* bottom, const char_t* front, const char_t* back)
{
    const char_t* images[6];
    u32_t id, i;

    images[0] = right;
    images[1] = left;
    images[2] = top;
    images[3] = bottom;
    images[4] = front;
    images[5] = back;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    for (i = 0; i < 6; i++)
    {
        i32_t width, height, channels;
        void_t* data;

        if ((data = load_image_from_file(images[i], &width, &height)) == NULL)
        {
            printf("ERROR!%s%s\n", "Failed to load texture: ", images[i]);
            goto error;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return id;

error:
    glDeleteTextures(1, &id);

    return 0;
}

void gl_error_loop()
{
    u32_t error;

    while ((error = glGetError()) != GL_NO_ERROR)
    {
        printf("%s%d\n", "OPENGL, ERROR: ", error);
    }
}

#endif /* OS_WINDOWS */