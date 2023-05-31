#version 330 core

layout (location = 0) in vec3 vert_position;

out vec3 frag_uv;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(vert_position, 1.0);
    gl_Position.z = 0.0;
    frag_uv = vert_position.xzy;
} 