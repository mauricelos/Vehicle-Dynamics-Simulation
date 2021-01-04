#include <array>
#include <iostream>

#include "gtest/gtest.h"

#include "utils.h"
#include "vehicle_logger.h"
#include "vehicle_specification_parser.h"

namespace
{

class IntegrationTest : public ::testing::Test
{
  public:
    std::array<char*, 4> temp_args_race_{strdup("program_file_name"), strdup("-r"),
                                         strdup("vehicle_specifications/mazda_rx8_8HP70.yaml"),
                                         strdup("vehicle_specifications/mazda_rx8.yaml")};
    char* args_race_[4] = {temp_args_race_[0], temp_args_race_[1], temp_args_race_[2], temp_args_race_[3]};

    std::string expected_output{
        "Vehicle: Mazda RX-8 R3 8HP70\n0 - 100: 5.81s\n0 - 200: 24.74s\n100 - 200: 18.93s\nQuarter mile time: "
        "14.18s\nMax acceleration: 0.812616g\nMax velocity: 256.902km/h\nLog files stored at "
        "vehicle_specifications/\n\nVehicle: Mazda RX-8 R3\n0 - 100: 6.42s\n0 - 200: 25.31s\n100 - 200: "
        "18.89s\nQuarter mile time: 14.77s\nMax acceleration: 0.655781g\nMax velocity: 256.108km/h\nLog files stored "
        "at vehicle_specifications/\n\nMazda RX-8 R3 8HP70 wins 0 - 100 race (0.610000s faster)\nMazda RX-8 R3 8HP70 "
        "wins 0 - 200 race (0.570000s faster)\nMazda RX-8 R3 wins 100 - 200 race (0.040000s faster)\nMazda RX-8 R3 "
        "8HP70 wins quarter mile race (0.590000s faster)\nMazda RX-8 R3 8HP70 has higher acceleration (0.156835g "
        "stronger)\nMazda RX-8 R3 8HP70 has higher velocity (0.793890km/h faster)\n\n"};
};

TEST_F(IntegrationTest, IntegrationTestWithExistingYamlFiles)
{
    testing::internal::CaptureStdout();

    std::vector<VehicleStats> vehicle_stats{};
    for (const auto& vehicle_specification_path :
         Utils::GetVehicleSpecificationPaths(temp_args_race_.size(), args_race_))
    {
        VehicleLogger vehicle_logger{VehicleSpecificationParser::ParseVehicleSpecification(vehicle_specification_path),
                                     vehicle_specification_path};
        vehicle_logger.RunLogger();
        vehicle_logger.PrintLoggingResults();
        vehicle_stats.emplace_back(vehicle_logger.GetVehicleStats());
    }

    if (vehicle_stats.size() == 2 && Utils::HasRaceCommandLineOption(temp_args_race_.size(), args_race_))
    {
        std::cout << vehicle_stats.front().Race(vehicle_stats.back());
    }

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected_output);
}

} // namespace