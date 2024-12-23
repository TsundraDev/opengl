#version 460 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec3 pos;
in vec3 col;

out vec3 color;

void main() {
  gl_Position = proj * view * model * vec4(pos, 1.0f);
  color = col;
}
