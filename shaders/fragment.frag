#version 330 core

out vec4 color;
uniform vec3 vertexColor;

void main() {
  color = vec4(vertexColor, 1);
}
