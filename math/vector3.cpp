#include <cmath>
#include "math/vector3.hpp"
#include "math/vector3.hpp"

float math::Vector3::length() const {
  return sqrtf(x * x + y * y + z * z);
}

math::Vector3& math::Vector3::normal() {
  const auto len = length();
  if (len == 0) return *this;
  x /= len;
  y /= len;
  z /= len;
  return *this;  
}

math::Vector3 math::operator+(const Vector3& v1, const Vector3& v2) {
  const auto x = v2.x + v1.x;
  const auto y = v2.y + v1.y;
  const auto z = v2.z + v1.z;
  return Vector3{ x, y, z };
}

math::Vector3 math::operator-(const Vector3& v1) {
  return Vector3{ -v1.x, -v1.y, -v1.z };
}

math::Vector3 math::operator-(const Vector3& v1, const Vector3& v2) {
  return v1 + (-v2);
}
