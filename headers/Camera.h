#include <GLFW/glfw3.h>
#include "math/math.hpp"

class Camera {
private:
  float yaw = -90.0f;
  float pitch = 0.0f;
  float lastX;
  float lastY;
  math::Vector3 cameraPos;
  math::Vector3 cameraFront{ 0.0f, 0.0f, -1.0f };
  math::Vector3 cameraUp{ 0.0f, 1.0f, 0.0f };
  float deltaTime = 0.f;
  float lastFrame = 0.f;
  bool firstMouse = true;
  GLFWwindow* window;
public:
  Camera(GLFWwindow* window, math::Vector3 position);
  void refresh();
  void keyboardCallback();
  void onMouseMove(double xpos, double ypos);
  math::Matrix4x4 view();
};