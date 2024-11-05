#include "hints.h"
#include <GLFW/glfw3.h>
#include <map>

extern const std::map<int, int> hints {
  { GLFW_CONTEXT_VERSION_MINOR, 3 },
  { GLFW_CONTEXT_VERSION_MAJOR, 3 },
  { GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE },
};