#pragma once
#include "math/matrix4x4.hpp"
#include "math/vector3.hpp"

namespace math {
  Matrix4x4 translate(const Vector3& vector);
  Matrix4x4 rotate(const float angle, const Vector3& vector);
  Matrix4x4 scale(const Vector3& vector);
  float radians(float angles);
}
