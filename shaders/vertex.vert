#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colors;
layout (location = 2) in vec2 texCoords;

out vec3 vertexColor;
out vec2 textureCoords;

void main() {
  gl_Position = vec4(position, 1);
  vertexColor = colors;
  textureCoords = texCoords;
}
