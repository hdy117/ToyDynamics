#include "mz_particle_force_gen_registry.h"

namespace mz {
	uint64_t ParticleForceGen_Pair::id = 0;

	void ParticleForceGenRegistry::add(ParticlePtr particle, ParticleForceGenBasePtr particleForceGen) {
		if (particle.get() != nullptr && particleForceGen.get() != nullptr) {
			ParticleForceGen_Pair particleFroceGenPair(particle, particleForceGen);
			m_forceGen[particleFroceGenPair.getID()] = particleFroceGenPair;
		}
	}

	void ParticleForceGenRegistry::updateForces(const real& deltaTime) {
		for (auto& forceGen : m_forceGen) {
			auto particle = forceGen.second.particle;
			auto particleForceGen = forceGen.second.particleForceGen;

			if (particle.get() != nullptr && particleForceGen.get() != nullptr) {
				particleForceGen->updateParticle(particle, deltaTime);
			}
		}
	}
}