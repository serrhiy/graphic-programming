#include <cmath>
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
