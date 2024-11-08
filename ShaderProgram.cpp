#include <glad/glad.h>
#include <stdexcept>
#include <map>
#include "ShaderProgram.h"

constexpr auto bufsize = 512;

ShaderProgram::ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader)
  : id{ glCreateProgram() }
{
  int success{ 0 };
  glAttachShader(id, vertexShader.getId());
  glAttachShader(id, fragmentShader.getId());
  glLinkProgram(id);
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    char infolog[bufsize];
    glGetProgramInfoLog(id, bufsize, NULL, infolog);
    const auto error = std::string{ "Error in shader program:\n" };
    throw std::invalid_argument(error + infolog);
  }
  vertexShader.destroy();
  fragmentShader.destroy();
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(id);
}

void ShaderProgram::use() const {
  glUseProgram(id);
}

void ShaderProgram::createUniform(const char* name) {
  const int location = glGetUniformLocation(id, name);
  if (location == -1) {
    const auto error = std::string{ "Cannot find" } + name + "uniform";
    throw std::invalid_argument(error);
  }
  uniforms.insert({ std::string{ name }, location });
}

void ShaderProgram::uniform(const std::string& name, int x) {
  const auto location = uniforms.find(name);
  if (location == uniforms.end()) {
    const auto error = std::string{ "Cannot find" } + name + "uniform";
    throw std::invalid_argument(error);
  } 
  glUniform1i(location->second, x);
}

void ShaderProgram::uniform(const std::string& name, float x, float y, float z) {
  const auto location = uniforms.find(name);
  if (location == uniforms.end()) {
    const auto error = std::string{ "Cannot find" } + name + "uniform";
    throw std::invalid_argument(error);
  } 
  glUniform3f(location->second, x, y, z);
}
