#version 330 core

layout(location = 0) in vec3 vert_position;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(vert_position, 1.0);
}
