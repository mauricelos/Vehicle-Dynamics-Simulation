#include "gtest/gtest.h"

#define private public
#include "vehicle_stats.h"
#undef private

namespace
{

class VehicleStatsTest : public ::testing::Test
{
  public:
    VehicleStats vehicle_stats_{};
    const std::string expected_race_outcome_{
        "test_vehicle wins 0 - 100 race (0.000000s faster)\ntest_vehicle wins 0 - 200 race (0.000000s "
        "faster)\ntest_vehicle wins 100 - 200 race (0.000000s faster)\ntest_vehicle wins quarter mile race (0.000000s "
        "faster)\ntest_vehicle has higher acceleration (0.000000g stronger)\ntest_vehicle has higher velocity "
        "(0.000000km/h faster)\n\n"};

    const std::string expected_second_race_outcome_{
        "test_vehicle wins 0 - 100 race (0.000000s faster)\ntest_vehicle wins 0 - 200 race (0.000000s "
        "faster)\ntemp_vehicle_stats wins 100 - 200 race (2.000000s faster)\ntemp_vehicle_stats wins quarter mile race "
        "(2.000000s faster)\ntest_vehicle has higher acceleration (0.000000g stronger)\ntest_vehicle has higher "
        "velocity (0.000000km/h faster)\n\n"};

    const std::string expected_vehicle_stats_out_{
        "Vehicle: test_vehicle\n0 - 100: 5s\n0 - 200: 20s\n100 - 200: 15s\nQuarter "
        "mile time: 14s\nMax acceleration: 0.815494g\nMax velocity: 180km/h\n"};

    void SetUp()
    {
        vehicle_stats_.SetVehicleName("test_vehicle");
        vehicle_stats_.SetZeroToHundredTime(5.0);
        vehicle_stats_.SetZeroToTwoHundredTime(20.0);
        vehicle_stats_.SetHundredToTwoHundredTime(15.0);
        vehicle_stats_.SetQuarterMileTime(14.0);
        vehicle_stats_.SetMaxAcceleration(8.0);
        vehicle_stats_.SetMaxVelocity(50.0);
    }
};

TEST_F(VehicleStatsTest, VehicleStatsSetterTest)
{
    EXPECT_EQ(vehicle_stats_.vehicle_name_, "test_vehicle");
    EXPECT_DOUBLE_EQ(vehicle_stats_.zero_to_hundred_time_, 5.0);
    EXPECT_DOUBLE_EQ(vehicle_stats_.zero_to_two_hundred_time_, 20.0);
    EXPECT_DOUBLE_EQ(vehicle_stats_.hundred_to_two_hundred_time_, 15.0);
    EXPECT_DOUBLE_EQ(vehicle_stats_.quarter_mile_time_, 14.0);
    EXPECT_DOUBLE_EQ(vehicle_stats_.GetMaxAcceleration(), 8.0);
    EXPECT_DOUBLE_EQ(vehicle_stats_.GetMaxVelocity(), 50.0);
}

TEST_F(VehicleStatsTest, RaceTest)
{
    EXPECT_EQ(vehicle_stats_.Race(vehicle_stats_), expected_race_outcome_);

    auto temp_vehicle_stats = vehicle_stats_;
    temp_vehicle_stats.SetVehicleName("temp_vehicle_stats");
    temp_vehicle_stats.SetHundredToTwoHundredTime(13.0);
    temp_vehicle_stats.SetQuarterMileTime(12.0);

    EXPECT_EQ(temp_vehicle_stats.Race(vehicle_stats_), expected_second_race_outcome_);
}

TEST_F(VehicleStatsTest, OstreamTest)
{
    std::ostringstream vehicle_stats_out;
    vehicle_stats_out << vehicle_stats_;
    EXPECT_EQ(vehicle_stats_out.str(), expected_vehicle_stats_out_);
}

} // namespace