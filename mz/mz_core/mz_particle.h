#pragma once

#include "mz_base.h"
#include "mz_integrator.h"

#include <string>

namespace mz {
	class Particle;
	using ParticlePtr = SharedPtr<Particle>;

	class SIM_API Particle {
	public:
		Particle();
		virtual ~Particle();
	public:
		/**
		 * @brief set init state of particle
		 * @param p 
		 * @param pdot 
		 * @param damping 
		 * @param mass 
		 * @param radius 
		*/
		void construct(const Position& p, const Velocity& pdot, const real& damping, const real& mass, const real& radius = 0.01);

		/**
		 * @brief add force to particle, like gravity, damping, drag force etc.
		 * @param force 
		 * @param actPointInParticle 
		*/
		void addForce(const Vector3& force, const Vector3& actPointInParticle = { 0,0,0 });

		/**
		 * @brief update particle
		 * @param deltaTime 
		*/
		void update(real deltaTime = 0.001);
	public:
		const Position& getPosition() const;
		const Velocity& getVelocity() const;
		const Acceleration& getAcceleration() const;
		const real& getDamping() const;	// unit N/(m/s)
		const real& getMass() const;
		const real& getInverseMass() const;
		bool hasFiniteMass() const;
	protected:
		void calAcceleration(const Vector3& force, const real& inverseMass);
		void clearForceAccum();
	protected:
		Position m_position;
		Velocity m_velocity;
		Acceleration m_acceleration;

		Vector3 m_forceAccum;

		real m_radius;
		real m_mass;
		real m_inverseMass;	// faster in integrator
		real m_damping;		// unit N/(m/s)

		std::string m_particleName;
		std::string m_particleID;

		IntegratorVector3Ptr m_velocityIntegrator;
		IntegratorVector3Ptr m_positionIntegrator;

		bool m_hasFiniteMass;
	};
}