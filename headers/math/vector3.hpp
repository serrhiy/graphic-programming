#pragma once

namespace math {
  struct Vector3 {
    float x;
    float y;
    float z;
    Vector3& normal();
    float length() const;
  };
}
