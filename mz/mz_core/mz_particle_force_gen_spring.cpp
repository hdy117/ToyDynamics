#include "mz_particle_force_gen_spring.h"

namespace mz {
  void ParticleForceGen_Spring::updateParticle(ParticlePtr particle,
    const real& deltaTime) {
    if (particle->hasFiniteMass() && mz::isNotNullPtr(particle) && mz::isNotNullPtr(m_other)) {
      Vector3 vecFromOtherToThis = particle->getPosition() - m_other->getPosition();

      auto deltaLength = vecFromOtherToThis.norm() - m_spParam.m_restLength;
      vecFromOtherToThis.normalize();
      
      // f = -k*(d-l_0)*d_hat, k is spring constant, 
      // l_0 is rest length, d is actual length, d_hat is direction from other to this particle
      // -k*(d-l_0) is the magnitude of spring force,
      // d_hat is the direction of spring force
      auto springForce = -m_spParam.m_springConstant * deltaLength * vecFromOtherToThis;

      // add spring force to this particle
      particle->addForce(springForce);
    }
  }

  void ParticleForceGen_AnchoredSpring::updateParticle(ParticlePtr particle,
    const real& deltaTime) {
    if (particle->hasFiniteMass() && mz::isNotNullPtr(particle)) {
      Vector3 vecFromOtherToThis = particle->getPosition() - m_anchor;

      auto deltaLength = vecFromOtherToThis.norm() - m_spParam.m_restLength;
      vecFromOtherToThis.normalize();

      // f = -k*(d-l_0)*d_hat, k is spring constant, 
      // l_0 is rest length, d is actual length, d_hat is direction from other to this particle
      // -k*(d-l_0) is the magnitude of spring force,
      // d_hat is the direction of spring force
      auto springForce = -m_spParam.m_springConstant * deltaLength * vecFromOtherToThis;

      // add spring force to this particle
      particle->addForce(springForce);
    }
  }
} // namespace mz