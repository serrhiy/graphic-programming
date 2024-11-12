#pragma once
#include "math/matrix4x4.hpp"
#include "math/vector3.hpp"

namespace math {
  Matrix4x4 translate(const Vector3& vector);
  Matrix4x4 rotate(const float angle, const Vector3& vector);
  Matrix4x4 scale(const Vector3& vector);
  Matrix4x4 perspective(float fov, float aspectRatio, float near, float far);
  Matrix4x4 lookAt(const Vector3& right, const Vector3& up, const Vector3& direction);
  float radians(float angles);
  Vector3 cross(const Vector3& first, const Vector3& second);
  float dot(const Vector3& first, const Vector3& second);
}
