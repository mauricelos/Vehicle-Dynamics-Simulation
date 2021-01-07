#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>

#include "engine.h"

double Engine::GetTorqueAtEngineSpeed(const double engine_speed) const
{
    return engine_torque_per_rpm_spline_(engine_speed);
}

std::uint16_t Engine::GetMaxEngineSpeed() const
{
    return max_engine_rpm_;
}

void Engine::SetEngineSpeed(const std::uint16_t engine_rpm)
{
    engine_rpm_ = engine_rpm;
}

double Engine::CalculateEngineTorque() const
{
    return (engine_rpm_ < max_engine_rpm_ + 20
                ? engine_torque_per_rpm_spline_(std::clamp(engine_rpm_, min_engine_rpm_, max_engine_rpm_))
                : 0.0);
}

double Engine::CalculateEngineHorsePower() const
{
    auto clamped_engine_rpm{std::clamp(engine_rpm_, min_engine_rpm_, max_engine_rpm_)};
    return (CalculateEngineTorque() * clamped_engine_rpm) / ((4500 / (2 * M_PI)) * 9.81);
}
