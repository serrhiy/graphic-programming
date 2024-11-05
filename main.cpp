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

const char* fragmentShaderOrange = "#version 330 core\n"
"out vec4 color;"
"void main() {"
"  color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
"}";

const char* fragmentShaderYellow = "#version 330 core\n"
"out vec4 color;"
"void main() {"
"  color = vec4(1.0f, 1.0f, 0.0f, 1.0f);"
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
  -0.5f, -0.5f, 0.0f,
   0.0f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f,

   0.0f,  0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f, -0.5f, 0.0f,
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

  const unsigned int shaderProgramOrange = createShaderProgram(vertexShaderSource, fragmentShaderOrange);
  const unsigned int shaderProgramYellow = createShaderProgram(vertexShaderSource, fragmentShaderYellow);
  
  unsigned int VBOs[]{ 0, 0 }, VAOs[]{ 0, 0 };
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);

  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points) / 2, points, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  
  glBindVertexArray(VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points) / 2, points + 9, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgramOrange);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgramYellow);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteProgram(shaderProgramOrange);
  glDeleteProgram(shaderProgramYellow);
  glDeleteBuffers(2, VBOs);
  glDeleteVertexArrays(2, VAOs);
  glfwTerminate();
  return 0;
}