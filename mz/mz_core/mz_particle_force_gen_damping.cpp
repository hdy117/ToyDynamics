#include "mz_particle_force_gen_damping.h"

namespace mz {
	void ParticleForceGen_Damping::updateParticle(ParticlePtr particle, const real& deltaTime ) {
		const auto& damping = particle->getDamping();

		if (particle->hasFiniteMass()) {
			particle->addForce(damping * particle->getVelocity());
		}
	}
}