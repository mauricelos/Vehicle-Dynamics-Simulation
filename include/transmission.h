///
/// @file transmission.h
///

#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <cstdint>
#include <vector>

class Transmission
{
  public:
    Transmission(const double drive_train_efficiency, const double final_drive_ratio,
                 const std::vector<double>& transmission_gear_ratios)
        : drive_train_efficiency_(drive_train_efficiency), final_drive_ratio_(final_drive_ratio),
          transmission_gear_ratios_(transmission_gear_ratios)
    {
        current_transmission_gear_ratio_ = transmission_gear_ratios[0];
    }
    std::uint16_t GetEngineSpeedNextGear() const;
    void SetMaxEngineSpeed(const std::uint16_t max_engine_speed);
    void SetEngineTorque(const double engine_torque);
    void SetEngineTorqueNextGear(const double engine_torque_next_gear);
    void SetWheelSpeed(const double wheel_speed);
    double CalculateWheelTorque() const;
    std::uint16_t CalculateEngineSpeed() const;
    void SelectGear();

  private:
    double CalculateWheelTorqueNextGear() const;
    double engine_torque_next_gear_{0.0};
    std::uint16_t max_engine_speed_{0};
    double engine_torque_{0.0};
    double wheel_speed_{0.0};
    std::uint8_t current_transmission_gear_{1};
    double current_transmission_gear_ratio_{0.0};
    const double drive_train_efficiency_;
    const double final_drive_ratio_;
    const std::vector<double> transmission_gear_ratios_;
};

#endif // TRANSMISSION_H
