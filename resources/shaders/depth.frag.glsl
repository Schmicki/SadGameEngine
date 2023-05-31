#version 330 core

layout(location = 0) out vec4 out_color;

void main()
{
    float ndc = (gl_FragCoord.z - 0.5) * 2 ;
    float depth = (0.2 / ndc) / 100.0;

    out_color = vec4(vec3(depth), 1.0);
}
