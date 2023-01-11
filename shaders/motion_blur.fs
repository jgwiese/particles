#version 460 core

uniform sampler2D texture_00;
uniform sampler2D texture_01;

in vec2 uv;
in vec3 normal;

layout(location = 0) out vec4 output_00;

void main()
{
    vec4 image_00 = texture(texture_00, uv);
    vec4 image_01 = texture(texture_01, uv);
    output_00 = 1.0 * image_01 + 0.8 * image_00;
}

