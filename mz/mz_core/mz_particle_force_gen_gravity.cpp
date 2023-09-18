#include "mz_particle_force_gen_gravity.h"

namespace mz {
	void ParticleForceGen_Gravity::updateParticle(ParticlePtr particle, const real& deltaTime) {
		const auto& gravity = getGravity();

		if (particle->hasFiniteMass()) {
			particle->addForce(gravity * particle->getInverseMass());
		}
	}
}