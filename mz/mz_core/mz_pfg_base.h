#pragma once

#include "mz_base.h"
#include "mz_particle.h"

namespace mz {
  class ParticleForceGenBase;
  using ParticleForceGenBasePtr = SharedPtr<ParticleForceGenBase>;

  class SIM_API ParticleForceGenBase {
  public:
    virtual void updateParticle(ParticlePtr particle,
                                const real &deltaTime = 0.001) = 0;
  };
} // namespace mz