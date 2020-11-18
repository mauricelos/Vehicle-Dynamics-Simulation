#include "vehicle.h"

void Vehicle::Init()
{
    transmission_.SetMaxEngineSpeed(engine_.GetMaxEngineSpeed());
}

void Vehicle::Step()
{
    transmission_.SetEngineTorque(engine_.CalculateEngineTorque());
    transmission_.SetEngineTorqueNextGear(engine_.GetTorqueAtEngineSpeed(transmission_.GetEngineSpeedNextGear()));
    transmission_.SelectGear();
    vehicle_model_.SetWheelTorque(transmission_.CalculateWheelTorque());
    transmission_.SetWheelSpeed(vehicle_model_.CalculateWheelSpeed());
    engine_.SetEngineSpeed(transmission_.CalculateEngineSpeed());
}

const std::string& Vehicle::GetVehicleName() const
{
    return vehicle_name_;
}

const Engine& Vehicle::GetEngine() const
{
    return engine_;
}

const Transmission& Vehicle::GetTransmission() const
{
    return transmission_;
}

const VehicleModel& Vehicle::GetVehicleModel() const
{
    return vehicle_model_;
}