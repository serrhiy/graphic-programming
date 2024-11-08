#include <glad/glad.h>
#include <fstream>
#include <string>
#include <sstream>
#include <variant>
#include <filesystem>
#include <stdexcept>
#include "Shader.hpp"

constexpr auto bufsize = 512;

std::string readFile(const std::string &path) {
  if (!std::filesystem::exists(path)) {
    const auto error = "File: " + path + " doesn\'t exist!";
    throw std::invalid_argument(error);
  }
  std::ifstream readable{ path };
  std::stringstream writable{ };
  writable << readable.rdbuf();
  return writable.str();
}

Shader::Shader(const std::string& path, const unsigned int type):
  source{ readFile(path) }, type{ type }, id{ glCreateShader(type) } 
{
  int success{ 0 };
  const auto cSource = source.c_str();
  glShaderSource(id, 1, &cSource, NULL);
  glCompileShader(id);
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infolog[bufsize]{ };
    glGetShaderInfoLog(id, bufsize, NULL, infolog);
    const auto error = "Error in " + path + " shader:\n" + infolog;
    throw std::invalid_argument(error);
  }
}

unsigned int Shader::getId() const { return id; }

void Shader::destroy() const {;
  glDeleteShader(id);
}

