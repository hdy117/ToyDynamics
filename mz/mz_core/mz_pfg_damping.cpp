#include "mz_pfg_damping.h"

namespace mz {
	void PFG_Damping::updateParticle(ParticlePtr particle, const real& deltaTime ) {
		const auto& damping = particle->getDamping();

		if (particle->hasFiniteMass()) {
			particle->addForce(-1.0f * damping * particle->getVelocity());
		}
	}
}