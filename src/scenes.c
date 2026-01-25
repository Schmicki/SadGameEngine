#include "scenes.h"

#if defined(OS_WINDOWS) /* OS_WINDOWS */

/*************************************************************************************************/

u8_t scene_light_new(scene_light_t* scene)
{
    u32_t i;
    mesh_data_t mesh_data;

    glGetIntegerv(GL_VIEWPORT, scene->viewport);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(0.0f);

    /* geometry */

    mesh_data = mesh_sphere(32, 1.0f);
    scene->sphere_mesh = gl_mesh_new(&mesh_data);
    mesh_free(&mesh_data);

    mesh_data = mesh_plane();
    scene->plane_mesh = gl_mesh_new(&mesh_data);
    mesh_free(&mesh_data);

    mesh_data = mesh_cube(0);
    scene->cube_mesh = gl_mesh_new(&mesh_data);
    mesh_free(&mesh_data);

    scene->camera.location = vec3_set(0.0f, -2.0f, 0.0f);
    scene->camera.scale = vec3_set(1.0f, 1.0f, 1.0f);
    scene->camera.rotation = vec3_set(0.0f, 0.0f, 0.0f);

    for (i = 0; i < SPHERE_COUNT; i++)
    {
        scene->spheres[i].location = vec3_set((flt_t)(rand() % SPHERE_RANGE),
            (flt_t)(rand() % SPHERE_RANGE), (flt_t)(rand() % SPHERE_RANGE));
        scene->spheres[i].scale = vec3_set(1.0f, 1.0f, 1.0f);
        scene->spheres[i].rotation = quat_euler_angles(vec3_set((flt_t)(rand() % 360),
            (flt_t)(rand() % 360), (flt_t)(rand() % 360)));
    }

    scene->light.location = vec3_set((flt_t)SPHERE_RANGE / 2, (flt_t)SPHERE_RANGE / 2 + 1.0f,
        (flt_t)SPHERE_RANGE / 2 - 1.0f);
    scene->light.rotation = vec4_set(0, 0, 0, 1);
    scene->light.scale = vec3_set(1, 1, 1);

    /* shaders */

    scene->sphere_shader = gl_pipeline_from_files("resources/shaders/shaded.vert.glsl",
        "resources/shaders/shaded.frag.glsl");

    scene->light_shader = gl_pipeline_from_files("resources/shaders/emissive.vert.glsl",
        "resources/shaders/emissive.frag.glsl");

    scene->effect_shader = gl_pipeline_from_files("resources/shaders/effect.vert.glsl",
        "resources/shaders/effect.frag.glsl");

    scene->skybox_shader = gl_pipeline_from_files("resources/shaders/skybox.vert.glsl",
        "resources/shaders/skybox.frag.glsl");

    scene->texture0 = gl_image_from_file("resources/icon - 256x256.png");
    scene->texture1 = gl_image_from_file("resources/icon - 256x256.png");
    scene->skybox = gl_cubemap_from_files(
        "resources/textures/skybox/left.jpg",
        "resources/textures/skybox/right.jpg",
        "resources/textures/skybox/top.jpg",
        "resources/textures/skybox/bottom.jpg",
        "resources/textures/skybox/front.jpg",
        "resources/textures/skybox/back.jpg");

    glUseProgram(scene->sphere_shader);
    glUniform1i(glGetUniformLocation(scene->sphere_shader, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(scene->sphere_shader, "texture1"), 1);

    glUseProgram(scene->light_shader);
    glUniform1i(glGetUniformLocation(scene->light_shader, "texture0"), 0);
    glUniform1i(glGetUniformLocation(scene->light_shader, "texture1"), 1);

    glUseProgram(scene->effect_shader);
    glUniform3f(glGetUniformLocation(scene->effect_shader, "position"), -1.0f, -1.0f, 0.0f);
    glUniform3f(glGetUniformLocation(scene->effect_shader, "scale"), 2.0f, 2.0f, 1.0f);
    glUniform1i(glGetUniformLocation(scene->effect_shader, "screen_texture"), 0);

    glUseProgram(scene->skybox_shader);
    glUniform1i(glGetUniformLocation(scene->skybox_shader, "skybox"), 0);

    /* framebuffer */

    glGenFramebuffers(1, &scene->framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, scene->framebuffer);

    glGenTextures(1, &scene->color_attachment);
    glBindTexture(GL_TEXTURE_2D, scene->color_attachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scene->viewport[2], scene->viewport[3], 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &scene->depth_attachment);
    glBindRenderbuffer(GL_RENDERBUFFER, scene->depth_attachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scene->viewport[2], scene->viewport[3]);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, scene->color_attachment, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, scene->depth_attachment);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return TRUE;
}

void_t scene_light_free(scene_light_t* scene)
{
    glDeleteFramebuffers(1, &scene->framebuffer);
    gl_pipeline_free(scene->effect_shader);
    gl_pipeline_free(scene->sphere_shader);
    gl_pipeline_free(scene->light_shader);
    gl_pipeline_free(scene->skybox_shader);
    glDeleteRenderbuffers(1, &scene->depth_attachment);
    glDeleteTextures(1, &scene->color_attachment);
    glDeleteTextures(1, &scene->texture0);
    glDeleteTextures(1, &scene->texture1);
    glDeleteTextures(1, &scene->skybox);
    gl_mesh_free(&scene->sphere_mesh);
    gl_mesh_free(&scene->plane_mesh);
    gl_mesh_free(&scene->cube_mesh);
}

void_t scene_light_render(scene_light_t* scene, flt_t time, flt_t delta_time)
{
    mat4_t model, view, projection, mvp;
    transform_t light;
    flt_t sin_time;
    u32_t i;

    sin_time = flt_sin((time / 5) * (flt_t)PI) / 2.0f + 0.5f;
    light = scene->light;
    light.location = vec3_add(light.location, vec3_set((sin_time - 0.5f) * 40, 0.0f, 0.0f));

    /* rendering */

    projection = mat4_perspective_gl(90.0f, 960.0f / 540.0f, -0.2f, 0.0f);
    view = mat4_view(scene->camera.location, scene->camera.rotation);

    /* first pass */

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glDepthFunc(GL_GREATER);

    glBindFramebuffer(GL_FRAMEBUFFER, scene->framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* render spheres */

    glUseProgram(scene->sphere_shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene->texture0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene->texture1);
    glUniform1f(glGetUniformLocation(scene->sphere_shader, "alpha"), sin_time);
    glUniform3f(glGetUniformLocation(scene->sphere_shader, "light.position"), light.location.x,
        light.location.y, light.location.z);
    glUniform3f(glGetUniformLocation(scene->sphere_shader, "light.color"), 0.99f, 0.99f, 0.99f);
    glUniform3f(glGetUniformLocation(scene->sphere_shader, "light.forward"), 0.0f, 1.0f, 0.0f);
    glUniform3f(glGetUniformLocation(scene->sphere_shader, "camera_position"), scene->camera.location.x,
        scene->camera.location.y, scene->camera.location.z);
    glUniform3f(glGetUniformLocation(scene->sphere_shader, "material.ambient"), 0.40392f, 0.55686f, 0.59608f);
    glUniform1f(glGetUniformLocation(scene->sphere_shader, "material.specular"), 0.5f);
    glUniform1f(glGetUniformLocation(scene->sphere_shader, "material.roughness"), 15.0f / 16.0f);

    for (i = 0; i < SPHERE_COUNT; i++)
    {
        model = mat4_model(scene->spheres[i]);
        mvp = mat4_mvp(model, view, projection);
        glUniformMatrix4fv(glGetUniformLocation(scene->sphere_shader, "model"), 1, GL_TRUE, (GLfloat*)&model);
        glUniformMatrix4fv(glGetUniformLocation(scene->sphere_shader, "mvp"), 1, GL_TRUE, (GLfloat*)&mvp);
        gl_draw_mesh(&scene->sphere_mesh);
    }

    /* render light */

    glUseProgram(scene->light_shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene->texture0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene->texture1);
    glUniform1f(glGetUniformLocation(scene->light_shader, "alpha"), sin_time);
    
    model = mat4_model(light);
    mvp = mat4_mvp(model, view, projection);
    glUniformMatrix4fv(glGetUniformLocation(scene->light_shader, "mvp"), 1, GL_TRUE, (GLfloat*)&mvp);
    gl_draw_mesh(&scene->sphere_mesh);

    /* render skybox */

    glDepthFunc(GL_GEQUAL);
    glCullFace(GL_FRONT);

    glUseProgram(scene->skybox_shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene->skybox);

    mvp = mat4_mvp(mat4_scale(vec3_set(1.0f, 1.0f, 1.0f)), mat4_rotation(quat_inv(
        quat_euler_angles(scene->camera.rotation))), projection);
    glUniformMatrix4fv(glGetUniformLocation(scene->skybox_shader, "mvp"), 1, GL_TRUE, (GLfloat*)&mvp);
    gl_draw_mesh(&scene->cube_mesh);

    /* second pass */

    glDepthFunc(GL_GREATER);
    glDisable(GL_DEPTH_TEST);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    /* render plane */

    glCullFace(GL_BACK);
    glUseProgram(scene->effect_shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene->color_attachment);
    gl_draw_mesh(&scene->plane_mesh);
}

/*************************************************************************************************/

u8_t scene_depth_new(scene_depth_t* scene)
{

    u32_t i;
    mesh_data_t sphere_data;

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(0.0f);

    sphere_data = mesh_sphere(32, 1.0f);
    scene->sphere_mesh = gl_mesh_new(&sphere_data);
    mesh_free(&sphere_data);

    scene->camera.location = vec3_set(0.0f, -2.0f, 0.0f);
    scene->camera.scale = vec3_set(1.0f, 1.0f, 1.0f);
    scene->camera.rotation = vec3_set(0.0f, 0.0f, 0.0f);

    for (i = 0; i < SPHERE_COUNT; i++)
    {
        scene->spheres[i].location = vec3_set((flt_t)(rand() % SPHERE_RANGE),
            (flt_t)(rand() % SPHERE_RANGE), (flt_t)(rand() % SPHERE_RANGE));
        scene->spheres[i].scale = vec3_set(1.0f, 1.0f, 1.0f);
        scene->spheres[i].rotation = quat_euler_angles(vec3_set((flt_t)(rand() % 360),
            (flt_t)(rand() % 360), (flt_t)(rand() % 360)));
    }

    scene->shader = gl_pipeline_from_files("resources/shaders/depth.vert.glsl",
        "resources/shaders/depth.frag.glsl");

    return TRUE;
}

void_t scene_depth_free(scene_depth_t* scene)
{
    gl_mesh_free(&scene->sphere_mesh);
    gl_pipeline_free(scene->shader);
}

void_t scene_depth_render(scene_depth_t* scene, flt_t time, flt_t delta_time)
{
    mat4_t model, view, projection, mvp;
    u32_t i;

    /* rendering */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projection = mat4_perspective_gl(90.0f, 1920.0f / 1080.0f, -0.2f, 0.0f);
    view = mat4_view(scene->camera.location, scene->camera.rotation);

    /* render spheres */

    glUseProgram(scene->shader);

    for (i = 0; i < SPHERE_COUNT; i++)
    {
        model = mat4_model(scene->spheres[i]);
        mvp = mat4_mvp(model, view, projection);
        glUniformMatrix4fv(glGetUniformLocation(scene->shader, "mvp"), 1, GL_TRUE, (GLfloat*)&mvp);
        gl_draw_mesh(&scene->sphere_mesh);
    }
}

#endif /* OS_HAS_WINDOW */