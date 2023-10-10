#include "mz_core/mz_pfg_spring.h"
#include "mz_core/mz_pfg_damping.h"
#include "mz_core/mz_pfg_gravity.h"
#include "mz_core/mz_pfg_registry.h"


#ifdef _WIN32
#pragma comment(lib, "mz_core.lib")
#endif // _WIN32

/**
 * @brief demo of constant spring, spring connects 2 particles, spring connects anchor and 1 particle
 * @return 
*/
int main() {
  // registry for particle and particle force generator
  mz::PFG_RegistryPtr particleForceGenRegistry =
      MakeSharedPtr<mz::PFG_Registry>();

  // make particle
  mz::Vector3 particleA_Offset = { 0,0,-10 }, origin = { 0,0,0 };
  mz::real particleA_Mass = 1.0;
  mz::ParticlePtr particle = MakeSharedPtr<mz::Particle>();
  particle->construct(particleA_Offset, { 0, 0, 0 }, particleA_Mass, 0.1);

  // make PFG, particle force generator
  mz::PFG_GravityPtr gravityFG = MakeSharedPtr<mz::PFG_Gravity>();
  mz::PFG_DampingPtr dampingFG = MakeSharedPtr<mz::PFG_Damping>();
  mz::PFG_SpringPtr springFG = MakeSharedPtr<mz::PFG_Spring>();
  mz::PFG_AnchoredSpringPtr anchorSpringFG = MakeSharedPtr<mz::PFG_AnchoredSpring>();
  
  mz::SpringParameter sp;
  sp.m_restLength = std::abs(particleA_Offset[2]);
  sp.m_springConstant = 10.0f * particleA_Mass;
  
  springFG->setSpringParamter(sp);
  anchorSpringFG->setSpringParamter(sp);

  anchorSpringFG->setAnchorPosition(origin);

  dampingFG->setDamping(1.0f);

  // register
  particleForceGenRegistry->add(particle, gravityFG);
  particleForceGenRegistry->add(particle, anchorSpringFG);
  particleForceGenRegistry->add(particle, dampingFG);

  mz::real t = 0.0f, dt = 0.001f, stopTime = 10.0f;

  // set gravity
  mz::setGravity();

  while (t < stopTime) {
    particleForceGenRegistry->updateForces(dt);
    particle->update();

    mz::Vector3Utils::debugPrintVector3("position", particle->getPosition());
    mz::Vector3Utils::debugPrintVector3("velocity", particle->getVelocity());
    mz::Vector3Utils::debugPrintVector3("acceleration", particle->getAcceleration());

    LOG_0 << MZ_SEPERATOR;

    t += dt;
  }

  return 0;
}