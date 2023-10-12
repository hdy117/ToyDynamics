#pragma once

#include "mz_pfg_base.h"

namespace mz {
class PFG_Damping;
using PFG_DampingPtr = MzSharedPtr<PFG_Damping>;

/**
 * @brief PFG means particle force generator. damping force generator, unit
 * N/(m/s)
 */
class SIM_API PFG_Damping : public ParticleForceGenBase {
public:
  PFG_Damping() : m_damping(0.0f) {}
  inline void setDamping(real damping) { m_damping = damping; }
  real getDamping() const { return m_damping; }

public:
  virtual void updateParticle(ParticlePtr particle,
                              const real &deltaTime = 0.001) override;

private:
  real m_damping;
};
} // namespace mz