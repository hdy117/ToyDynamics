#include "mz_particle.h"

namespace mz {
	Particle::Particle() {
		m_position = { 0,0,0 };
		m_velocity = { 0,0,0 };
		m_acceleration = { 0,0,0 };
		m_hasFiniteMass = false;
		m_mass = 0.0;
		m_inverseMass = globalConstInfiniteMass;

		m_positionIntegrator = IntegratorVector3_Maker::makeIntegrator(getGlobalIntegratorType());
		m_velocityIntegrator = IntegratorVector3_Maker::makeIntegrator(getGlobalIntegratorType());

		if (m_positionIntegrator.get() == nullptr) {
			LOG_ERROR << "m_positionIntegrator is nullptr.\n";
			throw std::runtime_error("nullptr of position integrator.");
		}

		if (m_velocityIntegrator.get() == nullptr) {
			LOG_ERROR<< "m_velocityIntegrator is nullptr.\n";
			throw std::runtime_error("nullptr of velocity integrator.");
		}
	}

	Particle::~Particle() {}

	void Particle::construct(const Position& p, const Velocity& pdot, const real& mass, const real& radius) {
		m_position = p;
		m_velocity = pdot;
		m_acceleration = { 0,0,0 };
		m_mass = mass;
		m_radius = radius;

		clearForceAccum();

		if (std::abs(m_mass) < 1e-12) {
			m_inverseMass = globalConstInfiniteMass;
			m_mass = 0;
			m_hasFiniteMass = false;
		}
		else {
			m_inverseMass = 1.0f / m_mass;
			m_hasFiniteMass = true;
		}

		m_positionIntegrator->setInitState(m_position);
		m_velocityIntegrator->setInitState(m_velocity);
		
		clearForceAccum();
	}

	bool Particle::hasFiniteMass() const {
		return m_hasFiniteMass;
	}

	void Particle::addForce(const Vector3& force, const Vector3& actPointInParticle) {
		m_forceAccum += force;
	}

	void Particle::clearForceAccum() {
		m_forceAccum = { 0,0,0 };
	}

	void Particle::calAcceleration(const Vector3& force, const real& inverseMass) {
		m_acceleration = force * m_inverseMass;
	}

	void Particle::update(real deltaTime) {
		// calculate acceleration
		calAcceleration(m_forceAccum, m_inverseMass);

		// integrator
		m_velocityIntegrator->integrate(m_acceleration, m_velocity, deltaTime);
		m_positionIntegrator->integrate(m_velocity, m_position, deltaTime);

		// clear accumalated force
		clearForceAccum();
	}

	const Position& Particle::getPosition() const {
		return m_position;
	}

	const Velocity& Particle::getVelocity() const {
		return m_velocity;
	}

	const Acceleration& Particle::getAcceleration() const {
		return m_acceleration;
	}
	
	const real& Particle::getMass() const {
		return m_mass;
	}

	const real& Particle::getInverseMass() const {
		return m_inverseMass;
	}
}