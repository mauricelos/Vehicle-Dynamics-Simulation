///
/// @file vehicle_logger.h
///

#ifndef VEHICLE_LOGGER_H
#define VEHICLE_LOGGER_H

#include <fstream>
#include <string>

#include "vehicle.h"
#include "vehicle_stats.h"

class VehicleLogger
{
  public:
    explicit VehicleLogger(const Vehicle&& vehicle, const std::string& log_path = "")
        : vehicle_(std::move(vehicle)), log_path_(log_path.substr(0, log_path.find_last_of(".")))
    {
    }
    void RunLogger(const double logging_time_cap = 120);
    void PrintLoggingResults();
    VehicleStats GetVehicleStats();

  private:
    void InitLogFileWriter(const std::string& log_file_name);
    void WriteLogFile(double time, double driven_distance, double vehicle_speed, double vehicle_acceleration);
    void ShutDownLogFileWriter();
    Vehicle vehicle_;
    const std::string log_path_;
    std::ofstream log_file_writer_{};
    const double hundred_kmh_in_ms_{27.7778};
    const double two_hundred_kmh_in_ms_{55.5556};
    const double quarter_mile_{402.336};
    VehicleStats vehicle_stats_{};
};

#endif // VEHICLE_LOGGER_H