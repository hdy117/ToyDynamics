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
      MakeMzSharedPtr<mz::PFG_Registry>();
  mz::ParticlePtr particle = MakeMzSharedPtr<mz::Particle>();

  mz::PFG_GravityPtr gravityForceGen = MakeMzSharedPtr<mz::PFG_Gravity>();
  mz::PFG_DragPtr dragForceGen = MakeMzSharedPtr<mz::PFG_Drag>();
  mz::PFG_DampingPtr dampingForceGen = MakeMzSharedPtr<mz::PFG_Damping>();

  dampingForceGen->setDamping(0.01);
  dragForceGen->setK1K2(0.01, 0.002);

  particleForceGenRegistry->add(particle, gravityForceGen);
  particleForceGenRegistry->add(particle, dragForceGen);
  particleForceGenRegistry->add(particle, dampingForceGen);

  // horizontal velocity will be consumed by drag force
  // vertical velocity will become constant by drage force and gravity force
  particle->construct({0, 0, 10}, {10, 0, 10}, 1.0, 0.1);

  mz::real t = 0.0f, dt = 0.001f, stopTime = 20.0f;

  mz::setGravity();

  while (t < stopTime) {
    particleForceGenRegistry->updateForces(dt);
    particle->update();

    mz::Vector3Utils::debugPrintVector3("position", particle->getPosition());
    mz::Vector3Utils::debugPrintVector3("velocity", particle->getVelocity());
    mz::Vector3Utils::debugPrintVector3("acceleration",
                                        particle->getAcceleration());

    LOG_0 << MZ_SEPERATOR;

    t += dt;
  }

  return 0;
}