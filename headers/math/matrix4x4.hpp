#pragma once
#include <cstddef>
#include "math/vector4.hpp"

namespace math {
  class Matrix4x4 {
  private:
    float* data;
  public:
    Matrix4x4();
    Matrix4x4(float x);
    Matrix4x4(float* matrix);
    Matrix4x4(const Matrix4x4& matrix);
    Matrix4x4& operator=(const Matrix4x4& matrix);
    float& operator[](size_t index) const;
    Matrix4x4 operator*(const Matrix4x4& matrix) const;
    Vector4 operator*(const Vector4& vec) const;
    float* pointer() const;
    ~Matrix4x4();
  };
}
