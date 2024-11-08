#include <cstddef>
#include "math/matrix4x4.hpp"

const size_t SIZE{ 4 };

math::Matrix4x4::Matrix4x4(): data{ new float[SIZE * SIZE]{  } } {

}

math::Matrix4x4::Matrix4x4(float x): Matrix4x4{  } {
  data[0] = data[5] = data[10] = data[15] = x;
}

math::Matrix4x4::Matrix4x4(float *matrix): data{ matrix } {

}

math::Matrix4x4::Matrix4x4(const Matrix4x4& matrix): Matrix4x4{  } {
  const float* otherData{ matrix.data };
  data[0] = otherData[0]; data[8] = otherData[8];
  data[1] = otherData[1]; data[9] = otherData[9];
  data[2] = otherData[2]; data[10] = otherData[10];
  data[3] = otherData[3]; data[11] = otherData[11];
  data[4] = otherData[4]; data[12] = otherData[12];
  data[5] = otherData[5]; data[13] = otherData[13];
  data[6] = otherData[6]; data[14] = otherData[14];
  data[7] = otherData[7]; data[15] = otherData[15];
}

math::Matrix4x4& math::Matrix4x4::operator=(const Matrix4x4& matrix) {
  const float* otherData{ matrix.data };
  data[0] = otherData[0]; data[8] = otherData[8];
  data[1] = otherData[1]; data[9] = otherData[9];
  data[2] = otherData[2]; data[10] = otherData[10];
  data[3] = otherData[3]; data[11] = otherData[11];
  data[4] = otherData[4]; data[12] = otherData[12];
  data[5] = otherData[5]; data[13] = otherData[13];
  data[6] = otherData[6]; data[14] = otherData[14];
  data[7] = otherData[7]; data[15] = otherData[15];
  return *this;
}

float &math::Matrix4x4::operator[](size_t index) const {
  return data[index];
}

math::Matrix4x4 math::Matrix4x4::operator*(const math::Matrix4x4& mat) const {
  const float* a{ data };
  const float* b{ mat.data };
  float* matrix{ new float[SIZE * SIZE]{  } };

  matrix[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
  matrix[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
  matrix[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
  matrix[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];

  matrix[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
  matrix[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
  matrix[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
  matrix[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];

  matrix[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12];
  matrix[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13];
  matrix[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
  matrix[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];

  matrix[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12];
  matrix[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13];
  matrix[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
  matrix[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];

  return Matrix4x4{ matrix };
}

math::Vector4 math::Matrix4x4::operator*(const Vector4& vec) const {
  float* vector{ new float[SIZE]{  } };
  float x{ data[0] * vec.x + data[1] * vec.y + data[2] * vec.z + data[3] * vec.w };
  float y{ data[4] * vec.x + data[5] * vec.y + data[6] * vec.z + data[7] * vec.w };
  float z{ data[8] * vec.x + data[9] * vec.y + data[10] * vec.z + data[11] * vec.w };
  float w{ data[12] * vec.x + data[13] * vec.y + data[14] * vec.z + data[15] * vec.w };
  return Vector4{ x, y, z, w };
}

float *math::Matrix4x4::pointer() const { return data; }

math::Matrix4x4::~Matrix4x4() {
  delete[] data;
}
