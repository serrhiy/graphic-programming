#version 330 core

in vec3 vertexColor;
in vec2 textureCoords;
out vec4 color;

uniform sampler2D obj1Texture;
uniform sampler2D obj2Texture;

void main() {
  color = mix(texture(obj1Texture, textureCoords), texture(obj2Texture, textureCoords), 0.2);
}
