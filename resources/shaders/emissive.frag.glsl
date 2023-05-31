#version 330 core

layout(location = 0) out vec4 out_color;

in vec4 vertex_color;
in vec3 vertex_normal;
in vec2 vertex_uv;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float alpha;

void main()
{
    out_color = mix(texture(texture0, vertex_uv), texture(texture1, vertex_uv), alpha);
    //out_color = vec4(vertex_normal, 1.0);
}
