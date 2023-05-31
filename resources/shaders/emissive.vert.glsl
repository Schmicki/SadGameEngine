#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

uniform mat4 mvp;

out vec4 vertex_color;
out vec3 vertex_normal;
out vec2 vertex_uv;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    vertex_color = color;
    vertex_normal = vec3(mvp * vec4(normal, 1.0));
    vertex_uv = uv;
}
