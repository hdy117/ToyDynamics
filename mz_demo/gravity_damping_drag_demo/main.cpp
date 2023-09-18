#include "mz_core/mz_particle_force_gen_registry.h"
#include "mz_core/mz_particle_force_gen_gravity.h"
#include "mz_core/mz_particle_force_gen_damping.h"
#include "mz_core/mz_particle_force_gen_drag.h"

#ifdef _WIN32
#pragma comment(lib,"mz_core.lib")
#endif // _WIN32

int main() {
	mz::ParticleForceGenRegistryPtr particleForceGenRegistry = MakeSharedPtr<mz::ParticleForceGenRegistry>();
	mz::ParticlePtr particle = MakeSharedPtr<mz::Particle>();

	mz::ParticleForceGen_GravityPtr gravityForceGen = MakeSharedPtr<mz::ParticleForceGen_Gravity>();
	mz::ParticleForceGen_DragPtr dragForceGen = MakeSharedPtr<mz::ParticleForceGen_Drag>();

	dragForceGen->setK1K2(0.01, 0.002);

	particleForceGenRegistry->add(particle, gravityForceGen);
	particleForceGenRegistry->add(particle, dragForceGen);

	particle->construct({ 0,0,10 }, { 0,0,10 }, 0.01, 1.0, 0.1);

	mz::real t = 0.0f, dt=0.001f;

	while (t < 3.0) {
		particleForceGenRegistry->updateForces(dt);
		particle->update();

		LOG_0 << "position:" << particle->getPosition() << "\n";
		LOG_0 << "velocity:" << particle->getVelocity() << "\n";
		LOG_0 << "acceleration:" << particle->getAcceleration() << "\n";

		t += dt;
	}

	return 0;
}