#pragma once

#include "mz/precision.h"

namespace mz {
class Vector3 {
public:
  Vector3() : x(0.0f), y(0.0f), z(0.0f), padding(0.0f) {}
  virtual ~Vector3() {}

public:
  real x, y, z;

private:
  real padding;
};
} // namespace mz