#pragma once

#include "mz_base.h"

namespace mz {
/**
 * @brief integrator base type for vector3
*/
class SIM_API IntegratorVector3 {
public:
  IntegratorVector3() {}
  IntegratorVector3(const Vector3& initState);
  virtual ~IntegratorVector3() {}
public:
  void setInitState(const Vector3& initState);
  virtual void integrate(const Vector3& u, Vector3& y, const real deltaTime) = 0;

protected:
  Vector3 m_preState;
};

/**
 * @brief euler integrator for vector3
*/
class SIM_API EulerIntegrator : public IntegratorVector3 {
public:
  EulerIntegrator() {}
  EulerIntegrator(const Vector3& initState) :IntegratorVector3(initState) {}
  virtual ~EulerIntegrator() {}
public:
  virtual void integrate(const Vector3& u, Vector3& y, const real deltaTime) override;
};

/**
 * @brief RK4 integrator for vector3
*/
class SIM_API RK4Integrator : public IntegratorVector3 {
public:
  RK4Integrator() {}
  RK4Integrator(const Vector3& initState) :IntegratorVector3(initState) {}
  virtual ~RK4Integrator() {}
public:
  virtual void integrate(const Vector3& u, Vector3& y, const real deltaTime) override;
};

/**
 * @brief integrator builder class
*/
class SIM_API IntegratorVector3_Maker {
public:
  static IntegratorVector3Ptr makeIntegrator(const INTEGRATOR_TYPE& type);
};
} // namespace mz