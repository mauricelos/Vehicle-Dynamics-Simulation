#include "gtest/gtest.h"

#define private public
#include "vehicle.h"
#undef private

namespace
{

class VehicleTest : public ::testing::Test
{
  public:
    Vehicle vehicle_{"test_vehicle", Engine{1000, 7500, {{1000.0, 5000.0, 7500.0}, {100.0, 300.0, 500.0}}},
                     Transmission{0.85, 4.77, {4.0, 3.0, 2.0, 1.0, 0.8}},
                     VehicleModel{0.01, 1400, 9.81, 1.1, 0.65, "225/40 R19", 0.011, 1.202, 0.3, 2.04, 0.0}};

    void SetUp()
    {
        vehicle_.Init();
    }
};

TEST_F(VehicleTest, VehicleInitTest)
{
    EXPECT_EQ(vehicle_.GetTransmission().max_engine_speed_, 7500);
}

TEST_F(VehicleTest, VehicleStepTest)
{
    vehicle_.Step();

    EXPECT_NEAR(vehicle_.GetEngine().CalculateEngineHorsePower(), 14.2331, 0.01);
    EXPECT_DOUBLE_EQ(vehicle_.GetEngine().CalculateEngineTorque(), 100.0);

    EXPECT_NEAR(vehicle_.GetTransmission().CalculateWheelTorque(), 1621.8, 0.01);
#ifndef _MSC_VER
    EXPECT_NEAR(vehicle_.GetTransmission().CalculateWheelTorqueNextGear(), 720.453, 0.01);
#endif
    EXPECT_EQ(vehicle_.GetTransmission().GetEngineSpeedNextGear(), 14);

    EXPECT_NEAR(vehicle_.GetVehicleModel().GetVehicleAcceleration(), 3.46006, 0.01);
    EXPECT_NEAR(vehicle_.GetVehicleModel().GetVehicleDrivenDistance(), 0.0, 0.01);
    EXPECT_NEAR(vehicle_.GetVehicleModel().GetVehicleSpeed(), 0.0346006, 0.01);
#ifndef _MSC_VER
    EXPECT_NEAR(vehicle_.GetVehicleModel().CalculateWheelForce(), 4995.16, 0.01);
#endif
}

TEST_F(VehicleTest, VehicleNameTest)
{
    EXPECT_EQ(vehicle_.GetVehicleName(), "test_vehicle");
}

TEST_F(VehicleTest, EngineTest)
{
    auto& engine = vehicle_.GetEngine();

    EXPECT_EQ(engine.GetMaxEngineSpeed(), 7500);
    EXPECT_DOUBLE_EQ(engine.GetTorqueAtEngineSpeed(5000), 300.0);
    EXPECT_DOUBLE_EQ(engine.CalculateEngineTorque(), 100.0);
    EXPECT_NEAR(engine.CalculateEngineHorsePower(), 14.2331, 0.01);
}

TEST_F(VehicleTest, TransmissionTest)
{
    auto& transmission = vehicle_.GetTransmission();

    EXPECT_EQ(transmission.GetEngineSpeedNextGear(), 0);
    EXPECT_DOUBLE_EQ(transmission.CalculateWheelTorque(), 0.0);
#ifndef _MSC_VER
    EXPECT_DOUBLE_EQ(transmission.CalculateWheelTorqueNextGear(), 0.0);
#endif
}

TEST_F(VehicleTest, VehicleModelTest)
{
    auto& vehicle_model = vehicle_.GetVehicleModel();

    EXPECT_DOUBLE_EQ(vehicle_model.GetDeltaTime(), 0.01);
    EXPECT_DOUBLE_EQ(vehicle_model.GetVehicleAcceleration(), 0.0);
    EXPECT_DOUBLE_EQ(vehicle_model.GetVehicleDrivenDistance(), 0.0);
    EXPECT_DOUBLE_EQ(vehicle_model.GetVehicleSpeed(), 0.0);
#ifndef _MSC_VER
    EXPECT_DOUBLE_EQ(vehicle_model.CalculateWheelForce(), 0.0);
    EXPECT_NEAR(vehicle_model.CalculateRollingResistants(), 151.074, 0.01);
#endif
    EXPECT_NEAR(vehicle_model.CalculateTireDynamicRadius("225/40 R19"), 0.324674, 0.01);
}

} // namespace
