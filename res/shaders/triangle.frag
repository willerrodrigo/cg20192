#version 330 core

in vec3 N;

void main() {
    gl_FragColor = vec4((N+vec3(1.0f, 1.0f, 1.0f))*0.5, 1.0f);
}
