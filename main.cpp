#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cmath>
#include "hints.h"
#include <Shader.h>
#include <ShaderProgram.h>

constexpr int width = 800;
constexpr int height = 600;
const char* title = "Graphic Programming";

void keyPress(GLFWwindow* window, int key, int scan, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void sizeChanging(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

const float points[] {
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f,
};

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

  const auto vertexShader = Shader("./shaders/vertex.vert", Shader::vertex);
  const auto fragmentShader = Shader("./shaders/fragment.frag", Shader::fragment);
  auto shaderProgram{ ShaderProgram{ vertexShader, fragmentShader } };
  
  unsigned int VBO{ 0 }, VAO{ 0 };
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof points, points, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  shaderProgram.use();
  shaderProgram.createUniform("vertexColor");
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const auto time = glfwGetTime();
    const auto green = sin(time) / 2 + 0.5;
    shaderProgram.uniform3f("vertexColor", 0.f, green, 0.0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glfwTerminate();
  return 0;
}