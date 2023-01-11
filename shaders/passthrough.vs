#version 460 core

layout (location = 0) in vec3 position_in;
layout (location = 1) in vec3 normal_in;
layout (location = 2) in vec2 uv_in;
layout (location = 3) in vec3 offset_in;

out vec2 uv;
out vec3 normal;


void main() {
    uv = uv_in;
    normal = normal_in;
    gl_Position = vec4(position_in, 1.0);
}

