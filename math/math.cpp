#define _USE_MATH_DEFINES
#include <cmath>
#include "math/math.hpp"

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

float math::radians(float angles) {
  return angles * M_PI / 180.0f;
}
