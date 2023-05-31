#version 330 core

out vec4 out_color;

in vec3 frag_uv;

uniform samplerCube skybox;

void main()
{    
    out_color = texture(skybox, frag_uv);
}