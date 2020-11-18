///
/// @file vehicle.h
///

#ifndef VEHICLE_H
#define VEHICLE_H

#include "engine.h"
#include "transmission.h"
#include "vehicle_model.h"

class Vehicle
{
  public:
    Vehicle(const std::string&& vehicle_name, const Engine&& engine, const Transmission&& transmission,
            const VehicleModel&& vehicle_model)
        : vehicle_name_(vehicle_name), engine_(std::move(engine)), transmission_(std::move(transmission)),
          vehicle_model_(std::move(vehicle_model))
    {
    }
    void Init();
    void Step();
    const std::string& GetVehicleName() const;
    const Engine& GetEngine() const;
    const Transmission& GetTransmission() const;
    const VehicleModel& GetVehicleModel() const;

  private:
    const std::string vehicle_name_;
    Engine engine_;
    Transmission transmission_;
    VehicleModel vehicle_model_;
};

#endif // VEHICLE_H