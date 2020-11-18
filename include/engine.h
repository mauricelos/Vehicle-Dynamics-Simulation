///
/// @file engine.h
///

#ifndef ENGINE_H
#define ENGINE_H

#include <cstdint>
#include <utility>
#include <vector>

#include "spline.h"

class Engine
{
  public:
    Engine(const std::uint16_t min_engine_rpm, const std::uint16_t max_engine_rpm,
           const std::pair<std::vector<double>, std::vector<double>>& engine_torque_per_rpm)
        : engine_rpm_(min_engine_rpm),
          min_engine_rpm_(min_engine_rpm < max_engine_rpm ? min_engine_rpm : max_engine_rpm),
          max_engine_rpm_(max_engine_rpm >= min_engine_rpm ? max_engine_rpm : min_engine_rpm)
    {
        engine_torque_per_rpm_spline_.set_points(engine_torque_per_rpm.first, engine_torque_per_rpm.second);
    }

    double GetTorqueAtEngineSpeed(const double engine_speed) const;
    std::uint16_t GetMaxEngineSpeed() const;
    void SetEngineSpeed(const std::uint16_t engine_rpm);
    double CalculateEngineTorque() const;
    double CalculateEngineHorsePower() const;

  private:
    tk::spline engine_torque_per_rpm_spline_{};
    std::uint16_t engine_rpm_{0};
    const std::uint16_t min_engine_rpm_;
    const std::uint16_t max_engine_rpm_;
};

#endif // ENGINE_H