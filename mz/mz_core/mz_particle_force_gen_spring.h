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

/**
 * @brief spring force base class
*/
class SIM_API SpringForceBase {
public:
  inline void setSpringParamter(const SpringParameter& sp) { m_spParam = sp; }
  inline const SpringParameter& getSpringParamter() { return m_spParam; }
protected:
  SpringParameter m_spParam;
};

/**
 * @brief constant spring parameter force, spring connects two particles
*/
class SIM_API ParticleForceGen_Spring : public SpringForceBase, public ParticleForceGenBase {
public:
  inline void setOtherParticle(ParticlePtr other) { m_other = other; }
public:
  virtual void updateParticle(ParticlePtr particle,
                              const real &deltaTime = 0.001) override;
protected:
  ParticlePtr m_other;
};

/**
 * @brief constant spring parameter force, spring connects one particle with an anchor
*/
class SIM_API ParticleForceGen_AnchoredSpring : public SpringForceBase, public ParticleForceGenBase {
public:
  inline void setAnchorPosition(const Vector3& anchor) { m_anchor = anchor; }
public:
  virtual void updateParticle(ParticlePtr particle,
    const real& deltaTime = 0.001) override;
protected:
  Vector3 m_anchor;
};
} // namespace mz