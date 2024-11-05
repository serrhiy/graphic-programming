#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "hints.h"

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

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;"
"void main() {"
"  gl_Position = vec4(position, 1);"
"}";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;"
"void main() {"
"  color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
"}";

unsigned int createShaderProgram(const char* vertexSource, const char* fragmentSource) {
  int success = 0;
  char infolog[512];
  const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
    throw std::invalid_argument(infolog);
  }
  const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glDeleteShader(vertexShader);
    glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
    throw std::invalid_argument(infolog);
  }
  const unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
    throw std::invalid_argument(infolog);
  }
  return shaderProgram;
}

const float points[] {
   0.5f,  0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
  -0.5f,  0.5f, 0.0f
};

const unsigned int indices[] {
  0, 1, 3,
  1, 2, 3
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

  const unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
  
  unsigned int VBO = 0, VAO = 0, EBO = 0;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof points, points, GL_STATIC_DRAW);
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteProgram(shaderProgram);
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glfwTerminate();
  return 0;
}