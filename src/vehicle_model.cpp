#define _USE_MATH_DEFINES
#include <cmath>

#include "vehicle_model.h"

double VehicleModel::GetDeltaTime() const
{
    return dt_;
}

double VehicleModel::GetVehicleSpeed() const
{
    return previous_vehicle_speed_;
}

double VehicleModel::GetVehicleDrivenDistance() const
{
    return driven_distance_;
}

double VehicleModel::GetVehicleAcceleration() const
{
    return acceleration_;
}

void VehicleModel::SetWheelTorque(const double wheel_torque)
{
    wheel_torque_ = wheel_torque;
}

void VehicleModel::CalculateVehicleDrivenDistance()
{
    driven_distance_ += previous_vehicle_speed_ * dt_;
}

double VehicleModel::CalculateWheelSpeed()
{
    return CalculateVehicleSpeed() / vehicle_wheel_dynamic_radius_ * 30 / M_PI;
}

double VehicleModel::CalculateVehicleSpeed()
{
    CalculateVehicleDrivenDistance();
    CalculateVehicleAcceleration();
    previous_vehicle_speed_ += acceleration_ * dt_;
    return previous_vehicle_speed_;
}

void VehicleModel::CalculateVehicleAcceleration()
{
    acceleration_ = (CalculateWheelForce() - CalculateRollingResistants()) / vehicle_mass_;
}

double VehicleModel::CalculateRollingResistants() const
{
    return (vehicle_mass_ * vehicle_gravity_ * sin(road_slope_) +
            vehicle_mass_ * vehicle_gravity_ * road_load_coefficient_ * cos(road_slope_) +
            0.5 * air_density_ * vehicle_drag_coefficient_ * vehicle_frontal_area_ * previous_vehicle_speed_ *
                previous_vehicle_speed_);
}

double VehicleModel::CalculateWheelForce() const
{
    return wheel_torque_ / vehicle_wheel_dynamic_radius_;
}

double VehicleModel::CalculateTireDynamicRadius(const std::string& tire_spec) const
{
    auto tire_width = std::stod(tire_spec.substr(0, tire_spec.find("/")));
    auto tire_height =
        std::stod(tire_spec.substr(tire_spec.find("/") + 1, tire_spec.find(" ") - (tire_spec.find("/") + 1)));
    auto tire_radius = std::stod(tire_spec.substr(tire_spec.find("R") + 1));

    return (tire_radius * 0.0254 * 0.5 + tire_height * tire_width / 1000 / 100) * 0.98;
}
