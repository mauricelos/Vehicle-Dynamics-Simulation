#include "vehicle.h"
#include "yaml-cpp/yaml.h"

#include "vehicle_specification_parser.h"

Vehicle VehicleSpecificationParser::ParseVehicleSpecification(const std::string& spec_file_path)
{
    YAML::Node vehicle_specification = YAML::LoadFile(spec_file_path);

    std::string vehicle_name{vehicle_specification["vehicle_name"].as<std::string>()};

    Engine engine{vehicle_specification["engine"]["engine_min_rpm"].as<std::uint16_t>(),
                  vehicle_specification["engine"]["engine_max_rpm"].as<std::uint16_t>(),
                  {vehicle_specification["engine"]["torque_curve"]["rpm"].as<std::vector<double>>(),
                   vehicle_specification["engine"]["torque_curve"]["torque"].as<std::vector<double>>()}};

    Transmission transmission{vehicle_specification["transmission"]["drivetrain_efficiency"].as<double>(),
                              vehicle_specification["transmission"]["final_drive_ratio"].as<double>(),
                              vehicle_specification["transmission"]["gear_ratios"].as<std::vector<double>>()};

    VehicleModel vehicle_model{vehicle_specification["time_per_step"].as<double>(),
                               vehicle_specification["vehicle_model"]["vehicle_mass"].as<double>() * 1.05 +
                                   vehicle_specification["vehicle_model"]["passenger_mass"].as<double>(),
                               vehicle_specification["vehicle_model"]["gravity"].as<double>(),
                               vehicle_specification["vehicle_model"]["tire_miua"].as<double>(),
                               vehicle_specification["vehicle_model"]["tire_load"].as<double>(),
                               vehicle_specification["vehicle_model"]["tire_spec"].as<std::string>(),
                               vehicle_specification["vehicle_model"]["road_load_coefficient"].as<double>(),
                               vehicle_specification["vehicle_model"]["air_density"].as<double>(),
                               vehicle_specification["vehicle_model"]["drag_coefficient"].as<double>(),
                               vehicle_specification["vehicle_model"]["fronal_area"].as<double>(),
                               vehicle_specification["vehicle_model"]["road_slope"].as<double>()};

    return Vehicle{std::move(vehicle_name), std::move(engine), std::move(transmission), std::move(vehicle_model)};
}
