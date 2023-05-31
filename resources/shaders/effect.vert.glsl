#version 330 core

layout(location = 0) in vec3 vert_position;
layout(location = 3) in vec2 vert_uv;

out vec2 frag_uv;

uniform vec3 position;
uniform vec3 scale;

void main()
{
    vec3 pos = position + scale * vert_position;
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
    frag_uv = vert_uv;
}
