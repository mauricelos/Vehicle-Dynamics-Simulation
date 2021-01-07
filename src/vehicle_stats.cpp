#include <iostream>

#include "vehicle_stats.h"

void VehicleStats::SetVehicleName(const std::string& vehicle_name)
{
    vehicle_name_ = vehicle_name;
}

void VehicleStats::SetZeroToHundredTime(const double zero_to_hundred_time)
{
    zero_to_hundred_time_ = zero_to_hundred_time;
}

void VehicleStats::SetZeroToTwoHundredTime(const double zero_to_two_hundred_time)
{
    zero_to_two_hundred_time_ = zero_to_two_hundred_time;
}

void VehicleStats::SetHundredToTwoHundredTime(const double hundred_to_two_hundred_time)
{
    hundred_to_two_hundred_time_ = hundred_to_two_hundred_time;
}

void VehicleStats::SetQuarterMileTime(const double quarter_mile_time)
{
    quarter_mile_time_ = quarter_mile_time;
}

void VehicleStats::SetMaxAcceleration(const double max_vehicle_acceleration)
{
    max_vehicle_acceleration_ = max_vehicle_acceleration;
}

void VehicleStats::SetMaxVelocity(const double max_vehicle_velocity)
{
    max_vehicle_velocity_ = max_vehicle_velocity;
}

double VehicleStats::GetMaxAcceleration() const
{
    return max_vehicle_acceleration_;
}

double VehicleStats::GetMaxVelocity() const
{
    return max_vehicle_velocity_;
}

std::string VehicleStats::Race(const VehicleStats& vehicle_stats)
{
    std::string race_result{};

    if (zero_to_hundred_time_ < vehicle_stats.zero_to_hundred_time_)
    {
        race_result += vehicle_name_ + " wins 0 - 100 race (" +
                       std::to_string(vehicle_stats.zero_to_hundred_time_ - zero_to_hundred_time_) + "s faster)\n";
    }
    else
    {
        race_result += vehicle_stats.vehicle_name_ + " wins 0 - 100 race (" +
                       std::to_string(zero_to_hundred_time_ - vehicle_stats.zero_to_hundred_time_) + "s faster)\n";
    }

    if (zero_to_two_hundred_time_ < vehicle_stats.zero_to_two_hundred_time_)
    {
        race_result += vehicle_name_ + " wins 0 - 200 race (" +
                       std::to_string(vehicle_stats.zero_to_two_hundred_time_ - zero_to_two_hundred_time_) +
                       "s faster)\n";
    }
    else
    {
        race_result += vehicle_stats.vehicle_name_ + " wins 0 - 200 race (" +
                       std::to_string(zero_to_two_hundred_time_ - vehicle_stats.zero_to_two_hundred_time_) +
                       "s faster)\n";
    }

    if (hundred_to_two_hundred_time_ < vehicle_stats.hundred_to_two_hundred_time_)
    {
        race_result += vehicle_name_ + " wins 100 - 200 race (" +
                       std::to_string(vehicle_stats.hundred_to_two_hundred_time_ - hundred_to_two_hundred_time_) +
                       "s faster)\n";
    }
    else
    {
        race_result += vehicle_stats.vehicle_name_ + " wins 100 - 200 race (" +
                       std::to_string(hundred_to_two_hundred_time_ - vehicle_stats.hundred_to_two_hundred_time_) +
                       "s faster)\n";
    }

    if (quarter_mile_time_ < vehicle_stats.quarter_mile_time_)
    {
        race_result += vehicle_name_ + " wins quarter mile race (" +
                       std::to_string(vehicle_stats.quarter_mile_time_ - quarter_mile_time_) + "s faster)\n";
    }
    else
    {
        race_result += vehicle_stats.vehicle_name_ + " wins quarter mile race (" +
                       std::to_string(quarter_mile_time_ - vehicle_stats.quarter_mile_time_) + "s faster)\n";
    }

    if (max_vehicle_acceleration_ > vehicle_stats.max_vehicle_acceleration_)
    {
        race_result += vehicle_name_ + " has higher acceleration (" +
                       std::to_string((max_vehicle_acceleration_ - vehicle_stats.max_vehicle_acceleration_) / 9.81) +
                       "g stronger)\n";
    }
    else
    {
        race_result += vehicle_stats.vehicle_name_ + " has higher acceleration (" +
                       std::to_string((vehicle_stats.max_vehicle_acceleration_ - max_vehicle_acceleration_) / 9.81) +
                       "g stronger)\n";
    }

    if (max_vehicle_velocity_ > vehicle_stats.max_vehicle_velocity_)
    {
        race_result += vehicle_name_ + " has higher velocity (" +
                       std::to_string((max_vehicle_velocity_ - vehicle_stats.max_vehicle_velocity_) * 3.6) +
                       "km/h faster)\n";
    }
    else
    {
        race_result += vehicle_stats.vehicle_name_ + " has higher velocity (" +
                       std::to_string((vehicle_stats.max_vehicle_velocity_ - max_vehicle_velocity_) * 3.6) +
                       "km/h faster)\n";
    }

    race_result += '\n';

    return race_result;
}

std::ostream& operator<<(std::ostream& os, const VehicleStats& vehicle_stats)
{
    os << "Vehicle: " << vehicle_stats.vehicle_name_ << '\n';
    os << "0 - 100: " << vehicle_stats.zero_to_hundred_time_ << "s" << '\n';
    os << "0 - 200: " << vehicle_stats.zero_to_two_hundred_time_ << "s" << '\n';
    os << "100 - 200: " << vehicle_stats.hundred_to_two_hundred_time_ << "s" << '\n';
    os << "Quarter mile time: " << vehicle_stats.quarter_mile_time_ << "s" << '\n';
    os << "Max acceleration: " << vehicle_stats.max_vehicle_acceleration_ / 9.81 << "g" << '\n';
    os << "Max velocity: " << vehicle_stats.max_vehicle_velocity_ * 3.6 << "km/h" << '\n';
    return os;
}
