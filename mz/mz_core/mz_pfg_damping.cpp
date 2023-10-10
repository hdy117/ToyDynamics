#include "mz_pfg_damping.h"

namespace mz {
	void PFG_Damping::updateParticle(ParticlePtr particle, const real& deltaTime ) {
		if (particle->hasFiniteMass()) {
			particle->addForce(-1.0f * m_damping * particle->getVelocity());
		}
	}
}