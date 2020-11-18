///
/// @file vehicle_model.h
///

#ifndef VEHICLE_MODEL_H
#define VEHICLE_MODEL_H

#include <string>

class VehicleModel
{
  public:
    VehicleModel(const double dt, const double vehicle_mass, const double vehicle_gravity,
                 const double vehicle_tire_miua, const double vehicle_tire_load, const std::string& vehicle_tire_spec,
                 const double road_load_coefficient, const double air_density, const double vehicle_drag_coefficient,
                 const double vehicle_frontal_area, const double road_slope)
        : dt_(dt), vehicle_mass_(vehicle_mass), vehicle_gravity_(vehicle_gravity),
          vehicle_tire_miua_(vehicle_tire_miua), vehicle_tire_load_(vehicle_tire_load),
          vehicle_wheel_dynamic_radius_(CalculateTireDynamicRadius(vehicle_tire_spec)),
          road_load_coefficient_(road_load_coefficient), air_density_(air_density),
          vehicle_drag_coefficient_(vehicle_drag_coefficient), vehicle_frontal_area_(vehicle_frontal_area),
          road_slope_(road_slope)
    {
    }
    double GetDeltaTime() const;
    double GetVehicleSpeed() const;
    double GetVehicleDrivenDistance() const;
    double GetVehicleAcceleration() const;
    void SetWheelTorque(const double wheel_torque);
    double CalculateWheelSpeed();
    double CalculateTireDynamicRadius(const std::string& tire_spec) const;

  private:
    void CalculateVehicleDrivenDistance();
    double CalculateVehicleSpeed();
    void CalculateVehicleAcceleration();
    double CalculateRollingResistants() const;
    double CalculateWheelForce() const;
    double previous_vehicle_speed_{0.0};
    double driven_distance_{0.0};
    double wheel_torque_{0.0};
    double acceleration_{0.0};
    const double dt_;
    const double vehicle_mass_;
    const double vehicle_gravity_;
    const double vehicle_tire_miua_;
    const double vehicle_tire_load_;
    const double vehicle_wheel_dynamic_radius_;
    const double road_load_coefficient_;
    const double air_density_;
    const double vehicle_drag_coefficient_;
    const double vehicle_frontal_area_;
    const double road_slope_;
};

#endif // VEHICLE_MODEL_H