#version 460 core
layout (location = 0) in vec3 position_in;
layout (location = 1) in vec3 normal_in;
layout (location = 2) in vec2 uv_in;
layout (location = 3) in vec3 offset_in;

out vec3 normal;
out vec2 uv;


void main()
{
    normal = normal_in;
    uv = uv_in;
    vec3 coordinates = 0.02 * position_in + offset_in;
    gl_Position = vec4(coordinates, 1.0);
}

