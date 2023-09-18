#pragma once

#include "mz_particle_force_gen_base.h"

namespace mz{
	class ParticleForceGen_Damping;
	using ParticleForceGen_DampingPtr = SharedPtr<ParticleForceGen_Damping>;

	class SIM_API ParticleForceGen_Damping : public ParticleForceGenBase {
	public:
		virtual void updateParticle(ParticlePtr particle,
			const real& deltaTime = 0.001) override;
	};
}