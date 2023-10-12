#pragma once

#include "mz_pfg_base.h"

namespace mz {
class PFG_Gravity;
using PFG_GravityPtr = MzSharedPtr<PFG_Gravity>;

class SIM_API PFG_Gravity : public ParticleForceGenBase {
public:
  virtual void updateParticle(ParticlePtr particle,
                              const real &deltaTime = 0.001) override;
};
} // namespace mz