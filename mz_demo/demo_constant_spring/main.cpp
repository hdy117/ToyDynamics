#include "mz_core/mz_pfg_damping.h"
#include "mz_core/mz_pfg_gravity.h"
#include "mz_core/mz_pfg_registry.h"
#include "mz_core/mz_pfg_spring.h"

#ifdef _WIN32
#pragma comment(lib, "mz_core.lib")
#endif // _WIN32

/**
 * @brief demo of constant spring, spring connects 2 particles, spring connects
 * anchor and 1 particle
 * @return
 */
int main() {
  // set log
  FLAGS_v = 1;

  // registry for particle and particle force generator
  mz::PFG_RegistryPtr particleForceGenRegistry =
      MakeMzSharedPtr<mz::PFG_Registry>();

  // make particle
  mz::Vector3 pA_Offset = {0, 0, -10}, origin = {0, 0, 0};
  mz::real particleMass = 1.0;
  mz::ParticlePtr pA = MakeMzSharedPtr<mz::Particle>();
  pA->construct(pA_Offset, {0, 0, 0}, particleMass, 0.1);
  mz::ParticlePtr pB = MakeMzSharedPtr<mz::Particle>();
  pB->construct(2.0f * pA_Offset, {0, 0, 0}, particleMass * 5.0f, 0.1);

  // make PFG, particle force generator
  mz::PFG_GravityPtr gravityFG = MakeMzSharedPtr<mz::PFG_Gravity>();
  mz::PFG_DampingPtr dampingFG = MakeMzSharedPtr<mz::PFG_Damping>();
  mz::PFG_SpringPtr springFG_AB =
      MakeMzSharedPtr<mz::PFG_Spring>(); // spring between A and B
  mz::PFG_AnchoredSpringPtr anchorSpringFG =
      MakeMzSharedPtr<mz::PFG_AnchoredSpring>();

  mz::SpringParameter sp;
  sp.m_restLength = std::abs(pA_Offset[2]);
  sp.m_springConstant = 10.0f * particleMass;

  springFG_AB->setSpringParamter(sp);
  springFG_AB->setOtherParticle(pA);

  anchorSpringFG->setSpringParamter(sp);
  anchorSpringFG->setAnchorPosition(origin);

  dampingFG->setDamping(1.0f);

  // register
  particleForceGenRegistry->add(pA, gravityFG);
  particleForceGenRegistry->add(pA, anchorSpringFG);
  particleForceGenRegistry->add(pA, dampingFG);

  particleForceGenRegistry->add(pB, springFG_AB);
  particleForceGenRegistry->add(pB, gravityFG);
  particleForceGenRegistry->add(pB, dampingFG);

  mz::real t = 0.0f, dt = 0.001f, stopTime = 30.0f;

  // set gravity
  mz::setGravity();

  while (t < stopTime) {
    particleForceGenRegistry->updateForces(dt);
    pA->update();
    pB->update();

    mz::Vector3Utils::debugPrintVector3("A position", pA->getPosition());
    mz::Vector3Utils::debugPrintVector3("A velocity", pA->getVelocity());
    mz::Vector3Utils::debugPrintVector3("A acceleration",
                                        pA->getAcceleration());

    LOG_0 << MZ_SEPERATOR;

    mz::Vector3Utils::debugPrintVector3("B position", pB->getPosition());
    mz::Vector3Utils::debugPrintVector3("B velocity", pB->getVelocity());
    mz::Vector3Utils::debugPrintVector3("B cceleration", pB->getAcceleration());

    LOG_0 << MZ_SEPERATOR;

    t += dt;
  }

  return 0;
}