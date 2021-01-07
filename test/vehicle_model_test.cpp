#include "gtest/gtest.h"

#define private public
#include "vehicle_model.h"
#undef private

namespace
{

class VehicleModelTest : public ::testing::Test
{
  public:
    VehicleModel vehicle_model_{0.01, 1400, 9.81, 1.1, 0.65, "225/40 R19", 0.011, 1.202, 0.3, 2.04, 0.0};
};

TEST_F(VehicleModelTest, GetterTest)
{
    EXPECT_DOUBLE_EQ(vehicle_model_.GetDeltaTime(), 0.01);
    EXPECT_DOUBLE_EQ(vehicle_model_.GetVehicleSpeed(), 0.0);
    EXPECT_DOUBLE_EQ(vehicle_model_.GetVehicleAcceleration(), 0.0);
}

TEST_F(VehicleModelTest, SetWheelTorqueTest)
{
    vehicle_model_.SetWheelTorque(1000.0);

    EXPECT_DOUBLE_EQ(vehicle_model_.wheel_torque_, 1000.0);
}

TEST_F(VehicleModelTest, CalculateTireDynamicRadiusTest)
{
    EXPECT_NEAR(vehicle_model_.CalculateTireDynamicRadius("225/40 R19"), 0.324674, 0.01);
}

TEST_F(VehicleModelTest, CalculateWheelSpeedTest)
{
    vehicle_model_.SetWheelTorque(1000.0);

    EXPECT_NEAR(vehicle_model_.CalculateWheelSpeed(), 0.615, 0.01);
}

#ifndef _MSC_VER

TEST_F(VehicleModelTest, CalculateWheelForceTest)
{
    EXPECT_DOUBLE_EQ(vehicle_model_.CalculateWheelForce(), 0.0);

    vehicle_model_.SetWheelTorque(1000.0);

    EXPECT_NEAR(vehicle_model_.CalculateWheelForce(), 3080.01, 0.01);
}

TEST_F(VehicleModelTest, CalculateRollingResistantsTest)
{
    EXPECT_NEAR(vehicle_model_.CalculateRollingResistants(), 151.074, 0.01);

    vehicle_model_.previous_vehicle_speed_ = 27.78;

    EXPECT_NEAR(vehicle_model_.CalculateRollingResistants(), 434.925, 0.01);
}

TEST_F(VehicleModelTest, CalculateVehicleAccelerationTest)
{
    vehicle_model_.SetWheelTorque(1000.0);
    vehicle_model_.CalculateVehicleAcceleration();

    EXPECT_NEAR(vehicle_model_.GetVehicleAcceleration(), 2.09, 0.01);
}

TEST_F(VehicleModelTest, CalculateVehicleSpeedTest)
{
    vehicle_model_.SetWheelTorque(1000.0);

    EXPECT_NEAR(vehicle_model_.CalculateVehicleSpeed(), 0.021, 0.01);
}

TEST_F(VehicleModelTest, CalculateVehicleDrivenDistanceTest)
{
    vehicle_model_.SetWheelTorque(1000.0);

    EXPECT_NEAR(vehicle_model_.CalculateVehicleSpeed(), 0.021, 0.01);

    vehicle_model_.CalculateVehicleDrivenDistance();

    EXPECT_NEAR(vehicle_model_.GetVehicleDrivenDistance(), 0.00021, 0.0001);
}

#endif

} // namespace
