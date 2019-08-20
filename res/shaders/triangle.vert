#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 C;

void main() {
    C = vec3(texture, 0.0f);
    gl_Position = projection * view * model * vec4(position, 1.0f);
}
