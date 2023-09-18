#pragma once

#include "mz_particle_force_gen_base.h"

namespace mz {
	class ParticleForceGen_Gravity;
	using ParticleForceGen_GravityPtr = SharedPtr<ParticleForceGen_Gravity>;

	class SIM_API ParticleForceGen_Gravity :public ParticleForceGenBase {
	public:
		virtual void updateParticle(ParticlePtr particle,
			const real& deltaTime = 0.001) override;
	};
}