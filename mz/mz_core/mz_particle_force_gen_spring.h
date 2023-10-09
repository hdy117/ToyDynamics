#pragma once

#include "mz_particle_force_gen_base.h"

namespace mz {
class ParticleForceGen_Spring;
using ParticleForceGen_SpringPtr = SharedPtr<ParticleForceGen_Spring>;

struct SIM_API SpringParameter {
  real m_springConstant;
  real m_restLength;

  SpringParameter() :m_springConstant(10.0f), m_restLength(1.0f) {}
};

class SIM_API ParticleForceGen_Spring : public ParticleForceGenBase {
public:
  inline void setOtherParticle(ParticlePtr other) { m_other = other; }
  inline void setSpringParamter(const SpringParameter& sp) { m_spParam = sp; }
  inline const SpringParameter& getSpringParamter() { return m_spParam; }
public:
  virtual void updateParticle(ParticlePtr particle,
                              const real &deltaTime = 0.001) override;
protected:
  SpringParameter m_spParam;
  ParticlePtr m_other;
};

class SIM_API ParticleForceGen_AnchoredSpring : public ParticleForceGenBase {
public:
  inline void setAnchorPosition(const Vector3& anchor) { m_anchor = anchor; }
  inline void setSpringParamter(const SpringParameter& sp) { m_spParam = sp; }
  inline const SpringParameter& getSpringParamter() { return m_spParam; }
public:
  virtual void updateParticle(ParticlePtr particle,
    const real& deltaTime = 0.001) override;
protected:
  SpringParameter m_spParam;
  Vector3 m_anchor;
};
} // namespace mz