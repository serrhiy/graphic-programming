#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cmath>
#include "hints.h"
#include <stb_image.h>
#include <Shader.h>
#include <ShaderProgram.h>

constexpr int width = 800;
constexpr int height = 600;
const char* title = "Graphic Programming";
const char* texturePath = "./textures/brick.jpg";

void keyPress(GLFWwindow* window, int key, int scan, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void sizeChanging(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

const float points[] {
  -0.5f, -0.5f, 0.0f,  1.f, 0.f, 0.f,  0.0f, 0.0f,
   0.5f, -0.5f, 0.0f,  0.f, 1.f, 0.f,  1.0f, 0.0f,
   0.0f,  0.5f, 0.0f,  0.f, 0.f, 1.f,  0.5f, 1.0f,
};

unsigned int loadTexture(const char* path) {
  unsigned int texture{ };
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width, height, channel;
  unsigned char* image = stbi_load(texturePath, &width, &height, &channel, 0);
  if (!image) throw std::runtime_error("Caannot load texture");
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  stbi_image_free(image);
  return texture;
}

int main(const int argc, const char* argv[]) {
  glfwInit();
  for (const auto [ hint, value ]: hints) glfwWindowHint(hint, value);
  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, sizeChanging);
  glfwSetKeyCallback(window, keyPress);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    return 1;
  }

  const auto vertexShader{ Shader{ "./shaders/vertex.vert", Shader::vertex } };
  const auto fragmentShader{ Shader{ "./shaders/fragment.frag", Shader::fragment } };
  auto shaderProgram{ ShaderProgram{ vertexShader, fragmentShader } };

  unsigned int texture = loadTexture(texturePath);
  
  unsigned int VBO{ 0 }, VAO{ 0 };
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof points, points, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  shaderProgram.use();
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteTextures(1, &texture);
  glfwTerminate();
  return 0;
}