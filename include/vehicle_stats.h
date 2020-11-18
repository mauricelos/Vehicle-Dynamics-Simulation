///
/// @file vehicle_stats.h
///

#ifndef VEHICLE_STATS_H
#define VEHICLE_STATS_H

#include <string>

class VehicleStats
{
  public:
    void SetVehicleName(const std::string& vehicle_name);
    void SetZeroToHundredTime(const double zero_to_hundred_time);
    void SetZeroToTwoHundredTime(const double zero_to_two_hundred_time);
    void SetHundredToTwoHundredTime(const double hundred_to_two_hundred_time);
    void SetQuarterMileTime(const double quarter_mile_time);
    void SetMaxAcceleration(const double max_vehicle_acceleration);
    void SetMaxVelocity(const double max_velocity);
    double GetMaxAcceleration() const;
    double GetMaxVelocity() const;
    std::string Race(const VehicleStats& vehicle_stats);
    friend std::ostream& operator<<(std::ostream& os, const VehicleStats& vehicle_stats);

  private:
    std::string vehicle_name_{};
    double zero_to_hundred_time_{0.0};
    double zero_to_two_hundred_time_{0.0};
    double hundred_to_two_hundred_time_{0.0};
    double quarter_mile_time_{0.0};
    double max_vehicle_acceleration_{0.0};
    double max_vehicle_velocity_{0.0};
};

#endif // VEHICLE_STATS_H