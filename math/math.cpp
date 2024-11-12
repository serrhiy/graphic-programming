#define _USE_MATH_DEFINES
#include <cmath>
#include "math/math.hpp"
#include "math/vector3.hpp"

constexpr auto SIZE{ 4 };

math::Matrix4x4 math::translate(const Vector3& vector) {
  float* matrix{ new float[SIZE * SIZE]{  } };
  matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.f;
  matrix[3] = vector.x;
  matrix[7] = vector.y;
  matrix[11] = vector.z;
  return Matrix4x4{ matrix };
}

math::Matrix4x4 math::rotate(const float angle, const Vector3& vector) {
  const float sina{ sinf(angle) };
  const float cosa{ cosf(angle) };
  const float x{ vector.x };
  const float y{ vector.y };
  const float z{ vector.z };
  float* matrix{ new float[SIZE * SIZE]{  } };
  matrix[0] = cosa + x * x * (1 - cosa);
  matrix[1] = x * y * (1 - cosa) - z * sina;
  matrix[2] = x * z * (1 - cosa) + y * sina;
  matrix[3] = 0.0f;
  matrix[4] = y * x * (1 - cosa) + z * sina;
  matrix[5] = cosa + y * y * (1 - cosa);
  matrix[6] = y * z * (1 - cosa) - x * sina;
  matrix[7] = 0.0f;
  matrix[8] = z * x * (1 - cosa) - y * sina;
  matrix[9] = z * y * (1 - cosa) + x * sina;
  matrix[10] = cosa + z * z * (1 - cosa);
  matrix[11] = 0.0f;
  matrix[12] = 0.0f;
  matrix[13] = 0.0f;
  matrix[14] = 0.0f;
  matrix[15] = 1.0f;
  return Matrix4x4{ matrix };
}

math::Matrix4x4 math::scale(const Vector3& vector) {
  float* matrix{ new float[SIZE * SIZE]{  } };
  matrix[0] = vector.x;
  matrix[5] = vector.y;
  matrix[10] = vector.z;
  matrix[15] = 1.f;
  return Matrix4x4{ matrix };
}

math::Matrix4x4 math::perspective(float angle, float ratio, float near, float far) {
  float* matrix{ new float[SIZE * SIZE]{  } };
  const float theta{ tanf(angle / 2) };
  matrix[0] = 1 / (ratio * theta);
  matrix[5] = 1 / (theta);
  matrix[10] = -(far + near) / (far - near);
  matrix[11] = -(2 * far * near) / (far - near);
  matrix[14] = -1;
  return Matrix4x4{ matrix };
}

float math::radians(float angles) {
  return angles * M_PI / 180.0f;
}

math::Vector3 math::cross(const Vector3& first, const Vector3& second) {
  const auto x = first.y * second.z - first.z * second.y;
  const auto y = first.z * second.x - first.x * second.z;
  const auto z = first.x * second.y - first.y * second.x;
  return Vector3{ x, y, z };
}

float math::dot(const Vector3& first, const Vector3& second) {
  return first.x * second.x + first.y * second.y + first.z * second.z;
}

math::Matrix4x4 math::lookAt(
  const Vector3& position,
  const Vector3& target,
  const Vector3& up
) {
  const auto direction = (position - target).normal();
  const auto right = math::cross(up, direction).normal();
  const auto newUp = math::cross(direction, right);
  auto matrix = new float[SIZE * SIZE]{  };
  matrix[0] = right.x;
  matrix[1] = right.y;
  matrix[2] = right.z;
  matrix[3] = -math::dot(right, position);
  matrix[4] = newUp.x;
  matrix[5] = newUp.y;
  matrix[6] = newUp.z;
  matrix[7] = -dot(newUp, position);
  matrix[8] = direction.x;
  matrix[9] = direction.y;
  matrix[10] = direction.z;
  matrix[11] = -dot(direction, position);
  matrix[15] = 1;
  return Matrix4x4{ matrix };
}