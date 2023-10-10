#pragma once

#include "mz_api.h"
#include "mz_log.h"
#include "mz_precision.h"

#include "Eigen/Dense"

#include <exception>
#include <cmath>
#include <string>

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
template<typename TyPtr>
bool isNullPtr(TyPtr&& ptr) { return ptr.get() == nullptr; }

template<typename TyPtr>
bool isNotNullPtr(TyPtr&& ptr) { return ptr.get() != nullptr; }

// integrator
 enum SIM_API INTEGRATOR_TYPE { FORWARD_EULER, RK4 };

class SIM_API IntegratorVector3;
using IntegratorVector3Ptr = SIM_API SharedPtr<IntegratorVector3>;

// global integrator
SIM_API void setGlobalIntergator(const INTEGRATOR_TYPE& integratorType = INTEGRATOR_TYPE::FORWARD_EULER);
SIM_API const INTEGRATOR_TYPE& getGlobalIntegratorType();

// vectors and rotation
using Vector3 = SIM_API Eigen::Vector3<mz::real>;
using Vector4 = SIM_API Eigen::Vector4<mz::real>;
using Quaternion = SIM_API Eigen::Quaternion<mz::real>;
using RotationMatrix = SIM_API Eigen::Matrix3<mz::real>;

class SIM_API Vector3Utils {
public:
	static void debugPrintVector3(const std::string& prefix, const Vector3& vector3);
};

// infinite mass thresh, for static object, whose mass is 0
const real globalConstInfiniteMass = 1e12;

// gravity 
SIM_API const Vector3& getGravity();
SIM_API void setGravity(const Vector3& gravity = { 0.0f,0.0f,-9.807f });

using Position = SIM_API Vector3;
using Velocity = SIM_API Vector3;
using Acceleration = SIM_API Vector3;
using EulerAngle = SIM_API Vector3;
using Omega = SIM_API Vector3;
using OmegaDot = SIM_API Vector3;

const Vector3 globalVector3_Zero = { 0,0,0 };
} // namespace mz