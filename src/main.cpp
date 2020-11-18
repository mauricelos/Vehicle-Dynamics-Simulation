#include <iostream>

#include "utils.h"
#include "vehicle_logger.h"
#include "vehicle_specification_parser.h"

int main(int argc, char** argv)
{
    std::vector<VehicleStats> vehicle_stats{};
    for (const auto& vehicle_specification_path : Utils::GetVehicleSpecificationPaths(argc, argv))
    {
        VehicleLogger vehicle_logger{VehicleSpecificationParser::ParseVehicleSpecification(vehicle_specification_path),
                                     vehicle_specification_path};
        vehicle_logger.RunLogger();
        vehicle_logger.PrintLoggingResults();
        vehicle_stats.emplace_back(vehicle_logger.GetVehicleStats());
    }

    if (vehicle_stats.size() == 2 && Utils::HasRaceCommandLineOption(argc, argv))
    {
        std::cout << vehicle_stats.front().Race(vehicle_stats.back());
    }

    std::cout << "Press enter to exit . . .";
    std::getchar();
    return 0;
}