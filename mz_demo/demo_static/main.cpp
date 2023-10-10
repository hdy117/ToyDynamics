#include "mz_core/mz_pfg_damping.h"
#include "mz_core/mz_pfg_drag.h"
#include "mz_core/mz_pfg_gravity.h"
#include "mz_core/mz_pfg_registry.h"


#ifdef _WIN32
#pragma comment(lib, "mz_core.lib")
#endif // _WIN32

/**
 * @brief demo of gravity and drag act on particle
 * @return 
*/
int main() {
  mz::PFG_RegistryPtr particleForceGenRegistry =
      MakeSharedPtr<mz::PFG_Registry>();
  mz::ParticlePtr particle = MakeSharedPtr<mz::Particle>();

  mz::PFG_GravityPtr gravityForceGen = MakeSharedPtr<mz::PFG_Gravity>();
  mz::PFG_DragPtr dragForceGen = MakeSharedPtr<mz::PFG_Drag>();
  mz::PFG_DampingPtr dampingForceGen = MakeSharedPtr<mz::PFG_Damping>();

  dragForceGen->setK1K2(0.01, 0.002);

  particleForceGenRegistry->add(particle, gravityForceGen);
  particleForceGenRegistry->add(particle, dragForceGen);
  particleForceGenRegistry->add(particle, dampingForceGen);

  const mz::real paritcleMass = 0;
  particle->construct({0, 0, 10}, {0, 0, 0}, paritcleMass, 0.1);

  mz::real t = 0.0f, dt = 0.001f, stopTime = 1.0f;

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