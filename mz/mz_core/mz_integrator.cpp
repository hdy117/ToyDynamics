#include "mz_integrator.h"

namespace mz {
IntegratorVector3::IntegratorVector3(const Vector3 &initState) {
  setInitState(initState);
}
void IntegratorVector3::setInitState(const Vector3 &initState) {
  m_preState = initState;
}
void EulerIntegrator::integrate(const Vector3 &u, Vector3 &y,
                                const real deltaTime) {
  y = m_preState + u * deltaTime;
  m_preState = y;
}
void RK4Integrator::integrate(const Vector3 &u, Vector3 &y,
                              const real deltaTime) {
  // @dongyuanhu
  throw std::runtime_error("RK4 integrator not implemented yet.");
}

IntegratorVector3Ptr
IntegratorVector3_Maker::makeIntegrator(const INTEGRATOR_TYPE &type) {
  IntegratorVector3Ptr integrator;
  if (type == INTEGRATOR_TYPE::FORWARD_EULER) {
    return MakeMzSharedPtr<EulerIntegrator>();
  } else if (type == INTEGRATOR_TYPE::RK4) {
    return MakeMzSharedPtr<RK4Integrator>();
  } else {
    LOG_ERROR << "unknown integrator type " << static_cast<int>(type) << "\n";
    throw std::runtime_error("unknow integrator type.");
  }

  return integrator;
}
} // namespace mz