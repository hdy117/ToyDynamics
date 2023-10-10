#include "mz_pfg_gravity.h"

namespace mz {
	void PFG_Gravity::updateParticle(ParticlePtr particle, const real& deltaTime) {
		const auto& gravity = getGravity();

		if (particle->hasFiniteMass()) {
			particle->addForce(gravity * particle->getMass());
		}
	}
}