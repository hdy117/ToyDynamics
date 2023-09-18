#include "mz_base.h"

namespace mz {
  INTEGRATOR_TYPE globalIntegratorType = INTEGRATOR_TYPE::FORWARD_EULER;
  Vector3 globalGravity = { 0.0f,0.0f,-9.807f };

  void setGlobalIntergator(const INTEGRATOR_TYPE& integratorType) {
    globalIntegratorType = integratorType;
  }

  const INTEGRATOR_TYPE& getGlobalIntegratorType() {
    return globalIntegratorType;
  }

  const Vector3& getGravity() {
    return globalGravity;
  }
  void setGravity(const Vector3& gravity) {
    globalGravity = gravity;
  }
  void SIM_API Vector3Utils::debugPrintVector3(const std::string& prefix, const Vector3& vector3) {
    LOG_0 << prefix << ", [x, y, z]:" << vector3.x() << ", " << vector3.y() << ", " << vector3.z() << "\n";
  }
}