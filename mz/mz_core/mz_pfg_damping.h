#pragma once

#include "mz_pfg_base.h"

namespace mz{
	class PFG_Damping;
	using PFG_DampingPtr = SharedPtr<PFG_Damping>;

	/**
	 * @brief PFG means particle force generator. damping force generator
	*/
	class SIM_API PFG_Damping : public ParticleForceGenBase {
	public:
		virtual void updateParticle(ParticlePtr particle,
			const real& deltaTime = 0.001) override;
	};
}