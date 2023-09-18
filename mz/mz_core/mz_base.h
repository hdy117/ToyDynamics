#pragma once

#include "mz_api.h"
#include "mz_log.h"
#include "mz_precision.h"

#include "Eigen/Dense"

#include <exception>
#include <cmath>

#ifdef USE_BOOST_SHARED_PTR
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

#define SharedPtr boost::shared_ptr
#define MakeSharedPtr boost::make_shared
#else
#include <memory>

#define SharedPtr std::shared_ptr
#define MakeSharedPtr std::make_shared
#endif // USE_STD_SHARED_PTR



namespace mz {
// integrator
SIM_API enum INTEGRATOR_TYPE { FORWARD_EULER, RK4 };

class IntegratorVector3;
using IntegratorVector3Ptr = SharedPtr<IntegratorVector3>;

// global integrator
SIM_API void setGlobalIntergator(const INTEGRATOR_TYPE& integratorType = INTEGRATOR_TYPE::FORWARD_EULER);
SIM_API const INTEGRATOR_TYPE& getGlobalIntegratorType();

// vectors and rotation
using Vector3 = Eigen::Vector3<real>;
using Vector4 = Eigen::Vector4<real>;
using Quaternion = Eigen::Quaternion<real>;
using RotationMatrix = Eigen::Matrix3<real>;

// gravity 
SIM_API const Vector3& getGravity();
SIM_API void setGravity(const Vector3& gravity = { 0.0f,0.0f,-9.807f });

using Position = Vector3;
using Velocity = Vector3;
using Acceleration = Vector3;
using EulerAngle = Vector3;
using Omega = Vector3;
using OmegaDot = Vector3;

const Vector3 globalVector3_Zero = { 0,0,0 };
} // namespace mz