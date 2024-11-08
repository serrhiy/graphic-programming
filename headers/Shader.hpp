#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
  private:
    const std::string source;
    const unsigned int id;
    const unsigned int type;
    bool destroyed = false;

  public:
    constexpr static unsigned int vertex = GL_VERTEX_SHADER;
    constexpr static unsigned int fragment = GL_FRAGMENT_SHADER;
    Shader(const std::string& path, const unsigned int type);
    unsigned int getId() const;
    void destroy() const;
};

