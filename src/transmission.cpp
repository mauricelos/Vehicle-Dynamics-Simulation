#include "transmission.h"

std::uint16_t Transmission::GetEngineSpeedNextGear() const
{
    return current_transmission_gear_ != transmission_gear_ratios_.size()
               ? wheel_speed_ * transmission_gear_ratios_[current_transmission_gear_] * final_drive_ratio_
               : CalculateEngineSpeed();
}

void Transmission::SetMaxEngineSpeed(const std::uint16_t max_engine_speed)
{
    max_engine_speed_ = max_engine_speed;
}

void Transmission::SetEngineTorque(const double engine_torque)
{
    engine_torque_ = engine_torque;
}

void Transmission::SetEngineTorqueNextGear(const double engine_torque_next_gear)
{
    engine_torque_next_gear_ = engine_torque_next_gear;
}

void Transmission::SetWheelSpeed(const double wheel_speed)
{
    wheel_speed_ = wheel_speed;
}

double Transmission::CalculateWheelTorque() const
{
    return drive_train_efficiency_ * current_transmission_gear_ratio_ * final_drive_ratio_ * engine_torque_;
}

std::uint16_t Transmission::CalculateEngineSpeed() const
{
    return wheel_speed_ * current_transmission_gear_ratio_ * final_drive_ratio_;
}

void Transmission::SelectGear()
{
    if ((CalculateEngineSpeed() >= max_engine_speed_ || CalculateWheelTorque() < CalculateWheelTorqueNextGear()) &&
        current_transmission_gear_ != transmission_gear_ratios_.size())
    {
        current_transmission_gear_ratio_ = transmission_gear_ratios_[++current_transmission_gear_ - 1];
    }
}

double Transmission::CalculateWheelTorqueNextGear() const
{
    return current_transmission_gear_ != transmission_gear_ratios_.size()
               ? drive_train_efficiency_ * transmission_gear_ratios_[current_transmission_gear_] * final_drive_ratio_ *
                     engine_torque_next_gear_
               : CalculateWheelTorque();
}