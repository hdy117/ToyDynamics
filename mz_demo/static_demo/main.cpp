#include "mz_core/mz_particle_force_gen_damping.h"
#include "mz_core/mz_particle_force_gen_drag.h"
#include "mz_core/mz_particle_force_gen_gravity.h"
#include "mz_core/mz_particle_force_gen_registry.h"


#ifdef _WIN32
#pragma comment(lib, "mz_core.lib")
#endif // _WIN32

/**
 * @brief demo of gravity and drag act on particle
 * @return 
*/
int main() {
  mz::ParticleForceGenRegistryPtr particleForceGenRegistry =
      MakeSharedPtr<mz::ParticleForceGenRegistry>();
  mz::ParticlePtr particle = MakeSharedPtr<mz::Particle>();

  mz::ParticleForceGen_GravityPtr gravityForceGen = MakeSharedPtr<mz::ParticleForceGen_Gravity>();
  mz::ParticleForceGen_DragPtr dragForceGen = MakeSharedPtr<mz::ParticleForceGen_Drag>();
  mz::ParticleForceGen_DampingPtr dampingForceGen = MakeSharedPtr<mz::ParticleForceGen_Damping>();

  dragForceGen->setK1K2(0.01, 0.002);

  particleForceGenRegistry->add(particle, gravityForceGen);
  particleForceGenRegistry->add(particle, dragForceGen);
  particleForceGenRegistry->add(particle, dampingForceGen);

  const mz::real paritcleMass = 0;
  particle->construct({0, 0, 10}, {0, 0, 0}, 0.01, paritcleMass, 0.1);

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