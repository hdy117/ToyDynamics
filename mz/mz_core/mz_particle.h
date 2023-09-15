#pragma once

#include "mz_base.h"
#include "mz_integrator.h"

namespace mz {
	class Particle {
	public:
		Particle();
		virtual ~Particle();
	public:
		void setInitState(const Position& p, const Velocity& pdot, const real& damping, const real& mass, const real& radius);

		void addExternalForce(const Vector3& force, const Vector3& actPointInParticle);
		void update(real deltaTime = 0.001);
	public:
		const Position& getPosition() const;
		const Velocity& getVelocity() const;
		const Acceleration& getAcceleration() const;
		const real& getDamping() const;
		const real& getMass() const;
	protected:
		void calAcceleration(const Vector3& force, const real& inverseMass);
		Vector3 calAllForce();
		void clearExternalForce();
		Vector3 calDampingForce(const real& damping, const Velocity& velocity);
	protected:
		Position m_position;
		Velocity m_velocity;
		Acceleration m_acceleration;
		real m_damping;		// unit N/(m/s)

		IntegratorVector3Ptr m_velocityIntegrator;
		IntegratorVector3Ptr m_positionIntegrator;

		real m_radius;
		real m_mass;
		real m_inverseMass;	// faster in integrator

		Vector3 m_externalForce;
	};
}