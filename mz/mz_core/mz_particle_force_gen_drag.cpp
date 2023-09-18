#include "mz_particle_force_gen_drag.h"

namespace mz {
	void ParticleForceGen_Drag::setK1K2(const real& k1, const real& k2) {
		m_k1 = k1;
		m_k2 = k2;
	}
	void ParticleForceGen_Drag::updateParticle(ParticlePtr particle, const real& deltaTime) {
		if (particle->hasFiniteMass()) {
			const auto& velocity = particle->getVelocity();
			const auto& normal = velocity.norm();
			const Vector3&& dragForce = -1.0f * velocity.normalized() * (m_k1 * normal + m_k2 * normal * normal);
			particle->addForce(dragForce);
		}
	}
}