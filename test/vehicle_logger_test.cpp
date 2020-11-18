#include "gtest/gtest.h"

#include "vehicle_logger.h"

namespace
{

class VehicleLoggerTest : public ::testing::Test
{
  public:
    VehicleLogger vehicle_logger_{
        Vehicle{"test_vehicle", Engine{1000, 7500, {{1000.0, 5000.0, 7500.0}, {100.0, 300.0, 500.0}}},
                Transmission{0.85, 4.77, {4.0, 3.0, 2.0, 1.0, 0.8}},
                VehicleModel{0.01, 1400, 9.81, 1.1, 0.65, "225/40 R19", 0.011, 1.202, 0.3, 2.04, 0.0}},
        "temp/"};
};

TEST_F(VehicleLoggerTest, Test)
{
    std::string first_line{};
    vehicle_logger_.RunLogger();

    // TODO: Implement unit tests
    // std::ifstream log_file("temp/_vehicle_log.csv");

    // if(log_file.good())
    // {
    //     std::getline(log_file, first_line);
    // }

    // EXPECT_EQ(first_line, "Time,Driven Distance,Vehicle Speed,Vehicle Acceleration,");
}

} // namespace