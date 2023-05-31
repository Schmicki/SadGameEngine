#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 frag_uv;

uniform sampler2D screen_texture;

void main()
{
    out_color = texture(screen_texture, frag_uv);
    //out_color = vec4(vec3((out_color.r + out_color.g + out_color.b) / 3), 1.0);
}
