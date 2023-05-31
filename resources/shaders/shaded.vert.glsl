#version 330 core

layout(location = 0) in vec3 vert_position;
layout(location = 1) in vec4 vert_color;
layout(location = 2) in vec3 vert_normal;
layout(location = 3) in vec2 vert_uv;

out vec3 frag_position;
out vec4 frag_color;
out vec3 frag_normal;
out vec2 frag_uv;

uniform mat4 model;
uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(vert_position, 1.0);
    frag_position = vec3(model * vec4(vert_position, 1.0));
    frag_color = vert_color;
    frag_normal = transpose(inverse(mat3(model))) * vert_normal;
    //frag_normal = mat3(model) * vert_normal;
    frag_uv = vert_uv;
}
