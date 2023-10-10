#include "mz_pfg_drag.h"

namespace mz {
	void PFG_Drag::setK1K2(const real& k1, const real& k2) {
		m_k1 = k1;
		m_k2 = k2;
	}
	void PFG_Drag::updateParticle(ParticlePtr particle, const real& deltaTime) {
		if (particle->hasFiniteMass()) {
			const auto& velocity = particle->getVelocity();
			const auto& normal = velocity.norm();
			const Vector3&& dragForce = -1.0f * velocity.normalized() * (m_k1 * normal + m_k2 * normal * normal);
			particle->addForce(dragForce);
		}
	}
}