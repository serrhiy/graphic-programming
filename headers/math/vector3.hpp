#pragma once

namespace math {
  struct Vector3 {
    float x;
    float y;
    float z;
    Vector3& normal();
    float length() const;
  };
  Vector3 operator-(const Vector3& v1, const Vector3& v2);
  Vector3 operator+(const Vector3& v1, const Vector3& v2);
  Vector3 operator-(const Vector3& v1);
}
