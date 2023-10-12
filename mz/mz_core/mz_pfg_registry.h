#pragma once

#include "mz_pfg_base.h"

#include <iostream>
#include <unordered_map>

namespace mz {
class SIM_API ParticleForceGen_Pair {
public:
  ParticlePtr particle;
  ParticleForceGenBasePtr particleForceGen;

  ParticleForceGen_Pair() {}

  /**
   * @brief construct particle force generator pair
   * @param particleIn
   * @param particleForceGenIn
   */
  ParticleForceGen_Pair(ParticlePtr particleIn,
                        ParticleForceGenBasePtr particleForceGenIn) {
    particle = particleIn;
    particleForceGen = particleForceGenIn;
    id++;
  }

  virtual ~ParticleForceGen_Pair() {}

  bool operator==(const ParticleForceGen_Pair &pfgPair) const {
    return id == pfgPair.getID();
  }

  /**
   * @brief get id of this particle force generator pair
   * @return
   */
  inline const uint64_t &getID() const { return id; }

private:
  static uint64_t id;
};

class PFG_Registry;
using PFG_RegistryPtr = MzSharedPtr<PFG_Registry>;

/**
 * @brief PFG is short for particle force generator
 */
class SIM_API PFG_Registry {
public:
  PFG_Registry(int defaultPairs = 1024) {
    m_forceGen.reserve(defaultPairs);
    clear();
  }
  virtual ~PFG_Registry() { clear(); }

public:
  /**
   * @brief add particle with its particle force generator into this registry
   * @param deltaTime
   */
  void add(ParticlePtr particle, ParticleForceGenBasePtr particleForceGen);

  /**
   * @brief update all particle forces registered in this registry
   */
  void updateForces(const real &deltaTime = 0.001);

  /**
   * @brief clear all registered particle and force generator. Note the memeory
   * will NOT be released.
   */
  inline void clear() { m_forceGen.clear(); }

protected:
  std::unordered_map<uint64_t, ParticleForceGen_Pair> m_forceGen;
};
} // namespace mz