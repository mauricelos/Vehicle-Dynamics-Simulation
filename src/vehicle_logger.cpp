#include <iostream>

#include "vehicle_logger.h"

void VehicleLogger::RunLogger(const double logging_time_cap)
{
    InitLogFileWriter("_vehicle_log.csv");
    double time{0.0};
    double start_hundred_to_two_hundred{0.0};
    vehicle_.Init();
    const auto& vehicle_model = vehicle_.GetVehicleModel();
    vehicle_stats_.SetVehicleName(vehicle_.GetVehicleName());

    while (time < logging_time_cap)
    {
        vehicle_.Step();
        time += vehicle_model.GetDeltaTime();

        if (vehicle_model.GetVehicleSpeed() <= hundred_kmh_in_ms_)
        {
            vehicle_stats_.SetZeroToHundredTime(time);
            start_hundred_to_two_hundred = time;
        }

        if (vehicle_model.GetVehicleSpeed() <= two_hundred_kmh_in_ms_)
        {
            vehicle_stats_.SetZeroToTwoHundredTime(time);
        }

        if (vehicle_model.GetVehicleSpeed() >= hundred_kmh_in_ms_ &&
            vehicle_model.GetVehicleSpeed() <= two_hundred_kmh_in_ms_)
        {
            vehicle_stats_.SetHundredToTwoHundredTime(time - start_hundred_to_two_hundred);
        }

        if (vehicle_model.GetVehicleDrivenDistance() <= quarter_mile_)
        {
            vehicle_stats_.SetQuarterMileTime(time);
        }

        if (vehicle_model.GetVehicleAcceleration() >= vehicle_stats_.GetMaxAcceleration())
        {
            vehicle_stats_.SetMaxAcceleration(vehicle_model.GetVehicleAcceleration());
        }

        if (vehicle_model.GetVehicleSpeed() >= vehicle_stats_.GetMaxVelocity())
        {
            vehicle_stats_.SetMaxVelocity(vehicle_model.GetVehicleSpeed());
        }

        WriteLogFile(time, vehicle_model.GetVehicleDrivenDistance(), vehicle_model.GetVehicleSpeed() * 3.6,
                     vehicle_model.GetVehicleAcceleration());
    }
    ShutDownLogFileWriter();
}

void VehicleLogger::InitLogFileWriter(const std::string& log_file_name)
{
    log_file_writer_.open(log_path_ + log_file_name);
    log_file_writer_ << "Time,Driven Distance,Vehicle Speed,Vehicle Acceleration," << '\n';
}

void VehicleLogger::ShutDownLogFileWriter()
{
    log_file_writer_.close();
}

void VehicleLogger::WriteLogFile(double time, double driven_distance, double vehicle_speed, double vehicle_acceleration)
{
    log_file_writer_ << std::to_string(time) << "," << std::to_string(driven_distance) << ","
                     << std::to_string(vehicle_speed) << "," << std::to_string(vehicle_acceleration) << '\n';
}

void VehicleLogger::PrintLoggingResults()
{
    std::cout << vehicle_stats_;
    std::cout << "Log files stored at "
              << log_path_.substr(0,
                                  log_path_.find_last_of("/") != std::string::npos ? log_path_.find_last_of("/") : 0) +
                     "/"
              << '\n'
              << '\n';

    log_file_writer_.open(log_path_ + "_vehicle_stats.txt");
    log_file_writer_ << vehicle_stats_;
    ShutDownLogFileWriter();
}

VehicleStats VehicleLogger::GetVehicleStats()
{
    return vehicle_stats_;
}
