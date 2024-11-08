#pragma once

#include "Shader.h"
#include <string>
#include <map>

class ShaderProgram {
  private:
    const unsigned int id;
    std::map<std::string, const int> uniforms{ };
  public:
    ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader);
    ~ShaderProgram();
    void use() const;
    void createUniform(const char* name);
    void uniform(const std::string& name, float x, float y, float z);
    void uniform(const std::string& name, int x);
};
