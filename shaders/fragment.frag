#version 330 core

in vec3 vertexColor;
in vec2 textureCoords;
out vec4 color;

uniform sampler2D objTexture;

void main() {
  color = texture(objTexture, textureCoords) * vec4(vertexColor, 1.0);
}
