#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Camera.h"
#include "math/math.hpp"

constexpr float cameraSpeed = 2.5;

Camera::Camera(GLFWwindow* window, math::Vector3 position):
window{ window }, cameraPos{ position } {
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  lastX = width / 2;
  lastY = height / 2;
  glfwSetWindowUserPointer(window, this);
  glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    camera->onMouseMove(x, y);
  });
}

void Camera::refresh() {
  const auto time = glfwGetTime();
  deltaTime = time - lastFrame;
  lastFrame = time;
  keyboardCallback();
}

void Camera::keyboardCallback() {
  auto speed = cameraSpeed * deltaTime;
  const auto cameraRight = math::cross(cameraFront, cameraUp).normal();
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPos += speed * cameraFront;
  }if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPos -= speed * cameraFront;
  } if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPos += speed * cameraRight;
  } if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPos -= speed * cameraRight;
  }
}

void Camera::onMouseMove(double xpos, double ypos) {
  constexpr float sensitivity = 0.1f;
  const auto xoffset = (xpos - lastX) * sensitivity;
  const auto yoffset = (lastY - ypos) * sensitivity;
  lastX = xpos;
  lastY = ypos;
  yaw += xoffset;
  pitch += yoffset;
  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;
  math::Vector3 front {
    cosf(math::radians(yaw)) * cosf(math::radians(pitch)),
    sinf(math::radians(pitch)),
    sinf(math::radians(yaw)) * cosf(math::radians(pitch))
  };
  cameraFront = front.normal();
}

math::Matrix4x4 Camera::view() {
  return math::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
