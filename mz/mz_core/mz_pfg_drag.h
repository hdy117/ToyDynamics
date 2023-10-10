#pragma once

#include "mz_pfg_base.h"

namespace mz {
	class PFG_Drag;
	using PFG_DragPtr = SharedPtr<PFG_Drag>;

	class SIM_API PFG_Drag :public ParticleForceGenBase {
	public:
		virtual void updateParticle(ParticlePtr particle,
			const real& deltaTime = 0.001) override;
	public:
		/**
		 * @brief -(k1*velocity+k2*pow(velocity,2))
		 * @param k1 
		 * @param k2 
		*/
		void setK1K2(const real& k1 = 0.01f, const real& k2 = 0.001f);
		
		inline const real& getK1() { return m_k1; }
		inline const real& getK2() { return m_k2; }
	protected:
		real m_k1;
		real m_k2;
	};
}