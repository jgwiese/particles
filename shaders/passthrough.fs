#version 460 core

uniform sampler2D texture_00;

in vec2 uv;
in vec3 normal;

layout(location = 0) out vec4 output_00;

void main()
{
    vec4 image_00 = texture(texture_00, uv);
    output_00 = image_00;
}


