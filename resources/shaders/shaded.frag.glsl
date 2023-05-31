#version 330 core

struct material_t
{
    vec3 ambient;
    sampler2D diffuse;
    float specular;
    float roughness;
};

struct light_t
{
    vec3 position;
    vec3 forward;
    vec3 color;
};

layout(location = 0) out vec4 out_color;

in vec3 frag_position;
in vec4 frag_color;
in vec3 frag_normal;
in vec2 frag_uv;

uniform material_t material;
uniform light_t light;

uniform sampler2D texture1;
uniform float alpha;
uniform vec3 camera_position;

float compute_spot_light_influence(vec3 to_light)
{
    return max(dot(to_light, normalize(-light.forward)) * 4 - 3, 0.0);
}

float compute_point_light_influence(vec3 to_light)
{
    return 1.0 / max(dot(to_light, to_light) / 40.0, 1.0);
}

void main()
{
    vec3 normal = normalize(frag_normal);
    vec3 to_light = light.position - frag_position;
    vec3 normal_to_light = normalize(to_light);
    vec3 to_camera = normalize(camera_position - frag_position);
    vec3 reflection = reflect(-normal_to_light, normal);

    float light_influence = compute_point_light_influence(to_light);
    float diffuse_value = max(dot(normal, normal_to_light), 0.0);
    float specular_value = material.specular * pow(max(dot(to_camera, reflection), 0.0), 64 * (1 - material.roughness));
    vec3 combined_light_color = material.ambient + (diffuse_value + specular_value) * light.color * light_influence;

    out_color = vec4(combined_light_color, 1.0) * mix(texture(material.diffuse, frag_uv), texture(texture1, frag_uv), alpha);
}
