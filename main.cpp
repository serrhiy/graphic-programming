#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cmath>
#include <stb_image.h>
#include <array>
#include "hints.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "math/math.hpp"

constexpr int width = 800;
constexpr int height = 600;
const char* title = "Graphic Programming";
const char* texture1Path = "./textures/brick.jpg";
const char* texture2Path = "./textures/awesomeface.png";

void keyPress(GLFWwindow* window, int key, int scan, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void sizeChanging(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

float points[] {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

const std::array cubePositions {
  math::Vector3( 0.0f,  0.0f,  0.0f), 
  math::Vector3( 2.0f,  5.0f, -15.0f), 
  math::Vector3(-1.5f, -2.2f, -2.5f),  
  math::Vector3(-3.8f, -2.0f, -12.3f),  
  math::Vector3( 2.4f, -0.4f, -3.5f),  
  math::Vector3(-1.7f,  3.0f, -7.5f),  
  math::Vector3( 1.3f, -2.0f, -2.5f),  
  math::Vector3( 1.5f,  2.0f, -2.5f), 
  math::Vector3( 1.5f,  0.2f, -1.5f), 
  math::Vector3(-1.3f,  1.0f, -1.5f)
};

auto firstMouse = true;
auto yaw = -90.0f;
float pitch = 0.0f;
float lastX = width / 2.0;
float lastY = height / 2.0;

math::Vector3 cameraPos = { 0.0f, 0.0f,  3.0f };
math::Vector3 cameraFront{ 0.0f, 0.0f, -1.0f };
constexpr math::Vector3 cameraUp{ 0.0f, 1.0f, 0.0f };
auto deltaTime = 0.f;
auto lastFrame = 0.f;

void processInput(GLFWwindow *window) {
  auto cameraSpeed = 2.5f * deltaTime;
  const auto cameraRight = math::cross(cameraFront, cameraUp).normal();
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPos += cameraSpeed * cameraFront;
  }if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPos -= cameraSpeed * cameraFront;
  } if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPos += cameraSpeed * cameraRight;
  } if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPos -= cameraSpeed * cameraRight;
  }
}
#include <iostream>
void mouse_callback(GLFWwindow * window, double xpos, double ypos) {
  constexpr float sensitivity = 0.1f;
  const auto xoffset = (xpos - lastX) * sensitivity;
  const auto yoffset = (lastY - ypos) * sensitivity;

  lastX = xpos;
  lastY = ypos;

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  math::Vector3 front {
    cosf(math::radians(yaw)) * cosf(math::radians(pitch)),
    sinf(math::radians(pitch)),
    sinf(math::radians(yaw)) * cosf(math::radians(pitch))
  };
  cameraFront = front.normal();
}

unsigned int loadTexture(const char* path, bool useAlpha) {
  unsigned int texture{ };
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width, height, channel;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* image = stbi_load(path, &width, &height, &channel, 0);
  if (!image) throw std::runtime_error("Caannot load texture");
  const int rgb = useAlpha ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, rgb, GL_UNSIGNED_BYTE, image);
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
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetFramebufferSizeCallback(window, sizeChanging);
  glfwSetKeyCallback(window, keyPress);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    return 1;
  }

  const auto vertexShader{ Shader{ "./shaders/vertex.vert", Shader::vertex } };
  const auto fragmentShader{ Shader{ "./shaders/fragment.frag", Shader::fragment } };
  auto shaderProgram{ ShaderProgram{ vertexShader, fragmentShader } };

  const unsigned int texture1 = loadTexture(texture1Path, false);
  const unsigned int texture2 = loadTexture(texture2Path, true);
  
  unsigned int VBO{ 0 }, VAO{ 0 };
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof points, points, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  shaderProgram.use();
  shaderProgram.createUniform("obj1Texture");
  shaderProgram.createUniform("obj2Texture");
  shaderProgram.createUniform("transform");
  shaderProgram.uniform("obj1Texture", 0);
  shaderProgram.uniform("obj2Texture", 1);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glEnable(GL_DEPTH_TEST);
  constexpr auto radius = 10;
  while (!glfwWindowShouldClose(window)) {
    const auto time = glfwGetTime();
    deltaTime = time - lastFrame;
    lastFrame = time;
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    processInput(window);
    const auto view = math::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    const auto projection = math::perspective(math::radians(45), (float)width / height, 0.1f, 100.f);
    auto index = 0;
    glBindVertexArray(VAO);
    for (const auto cubePosition: cubePositions) {
      const auto rotateVector{ math::Vector3{ 0.5f, 1.f, 0.f }.normal() };
      const auto rotate{ math::rotate(glfwGetTime() * (++index) / 2, rotateVector) };
      const auto translate{ math::translate(cubePosition) };
      const auto model{ translate * rotate };
      const auto transform{ projection * view * model };
      shaderProgram.uniform("transform", 1, true, transform.pointer());
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteTextures(1, &texture1);
  glDeleteTextures(1, &texture2);
  glfwTerminate();
  return 0;
}