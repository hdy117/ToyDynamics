#include "mz_pfg_spring.h"

namespace mz {
  Vector3 SpringForceBase::springForceCalculate(const Vector3& thisParticle, const Vector3& otherParticle) {
    Vector3 vecFromOtherToThis = thisParticle - otherParticle;

    auto deltaLength = vecFromOtherToThis.norm() - m_spParam.m_restLength;
    vecFromOtherToThis.normalize();

    // f = -k*(d-l_0)*d_hat, k is spring constant, 
    // l_0 is rest length, d is actual length, d_hat is direction from other to this particle
    // -k*(d-l_0) is the magnitude of spring force,
    // d_hat is the direction of spring force
    auto springForce = -m_spParam.m_springConstant * deltaLength * vecFromOtherToThis;

    return springForce;
  }

  void PFG_Spring::updateParticle(ParticlePtr particle,
    const real& deltaTime) {
    if (particle->hasFiniteMass() && mz::isNotNullPtr(particle) && mz::isNotNullPtr(m_other)) {
      auto springForce = springForceCalculate(particle->getPosition(), m_other->getPosition());

      // add spring force to this particle
      particle->addForce(springForce);

      // add spring force to other particle
      if (m_other->hasFiniteMass()) {
        m_other->addForce(-springForce);
      }
    }
  }

  void PFG_SpringBungee::updateParticle(ParticlePtr particle,
    const real& deltaTime) {
    if (particle->hasFiniteMass() && mz::isNotNullPtr(particle) && mz::isNotNullPtr(m_other)) {
      // if distance between two particle is less than bungee free length, then no force will be generate
      auto dist = (particle->getPosition() - m_other->getPosition()).norm();
      if (dist <= m_spParam.m_restLength) return;

      // calculate force if needed
      auto springForce = springForceCalculate(particle->getPosition(), m_other->getPosition());

      // add spring force to this particle
      particle->addForce(springForce);

      // add spring force to other particle
      if (m_other->hasFiniteMass()) {
        m_other->addForce(-springForce);
      }
    }
  }

  void PFG_AnchoredSpring::updateParticle(ParticlePtr particle,
    const real& deltaTime) {
    if (particle->hasFiniteMass() && mz::isNotNullPtr(particle)) {
      // calculate force if needed
      auto springForce = springForceCalculate(particle->getPosition(), m_anchor);

      // add spring force to this particle
      particle->addForce(springForce);
    }
  }
} // namespace mz