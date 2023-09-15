#include "mz_particle.h"

namespace mz {
	Particle::Particle() {
		m_position = { 0,0,0 };
		m_velocity = { 0,0,0 };
		m_acceleration = { 0,0,0 };
		m_damping = 0.0;

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

	void Particle::setInitState(const Position& p, const Velocity& pdot, const real& damping, const real& mass, const real& radius) {
		m_position = p;
		m_velocity = pdot;
		m_acceleration = { 0,0,0 };
		m_damping = damping;
		m_mass = mass;
		m_radius = radius;

		clearExternalForce();

		if (std::abs(m_mass) < 1e-12) {
			m_inverseMass = 1e12;
			m_mass = 0;
		}
		else {
			m_inverseMass = 1.0f / m_mass;
		}

		m_positionIntegrator->setInitState(m_position);
		m_velocityIntegrator->setInitState(m_velocity);
	}

	void Particle::addExternalForce(const Vector3& force, const Vector3& actPointInParticle) {
		m_externalForce += force;
	}

	void Particle::clearExternalForce() {
		m_externalForce = { 0,0,0 };
	}

	Vector3 Particle::calDampingForce(const real& damping, const Velocity& velocity) {
		// damping force
		Vector3 dampingForce = m_velocity * m_damping * (-1);
		return dampingForce;
	}

	void Particle::calAcceleration(const Vector3& force, const real& inverseMass) {
		m_acceleration = force * m_inverseMass;
	}

	Vector3 Particle::calAllForce() {
		// damping force
		Vector3&& dampingForce = calDampingForce(m_damping, m_velocity);
		Vector3&& gravityForce = m_mass * getGravity();

		return dampingForce + m_externalForce + gravityForce;
	}

	void Particle::update(real deltaTime) {
		auto&& allForce = calAllForce();
		calAcceleration(allForce, m_inverseMass);

		m_velocityIntegrator->integrate(m_acceleration, m_velocity, deltaTime);
		m_positionIntegrator->integrate(m_velocity, m_position, deltaTime);

		clearExternalForce();
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

	const real& Particle::getDamping() const {
		return m_damping;
	}
	
	const real& Particle::getMass() const {
		return m_mass;
	}
}