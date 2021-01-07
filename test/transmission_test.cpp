#include "gtest/gtest.h"

#define private public
#include "transmission.h"
#undef private

namespace
{

class TransmissionTest : public ::testing::Test
{
  public:
    Transmission transmission_{0.85, 4.77, {4.0, 3.0, 2.0, 1.0, 0.8}};

    void SetUp()
    {
        // Mandatory, needs fix!
        transmission_.SetMaxEngineSpeed(9000);
    }
};

#ifndef _MSC_VER

TEST_F(TransmissionTest, TransmissionConstructorTestNormal)
{
    transmission_.SelectGear();

    // Not correct when SetMaxEngineSpeed() not called before SelectGear() since CalculateEngineSpeed() -> 0.0 >=
    // max_engine_speed_ -> 0 == true!!!
    EXPECT_EQ(transmission_.current_transmission_gear_, 1);
    EXPECT_DOUBLE_EQ(transmission_.current_transmission_gear_ratio_, 4.0);
    EXPECT_DOUBLE_EQ(transmission_.CalculateEngineSpeed(), 0.0);
    EXPECT_DOUBLE_EQ(transmission_.CalculateWheelTorque(), 0.0);
    EXPECT_DOUBLE_EQ(transmission_.CalculateWheelTorqueNextGear(), 0.0);
    EXPECT_DOUBLE_EQ(transmission_.GetEngineSpeedNextGear(), 0.0);
}

#endif

TEST_F(TransmissionTest, GetEngineSpeedNextGearTest)
{
    transmission_.SetWheelSpeed(5000 / 4.77 / 4.0);

    EXPECT_EQ(transmission_.GetEngineSpeedNextGear(), 3749);
}

TEST_F(TransmissionTest, SetMaxEngineSpeedTest)
{
    transmission_.SetMaxEngineSpeed(9500);

    EXPECT_EQ(transmission_.max_engine_speed_, 9500);
}

TEST_F(TransmissionTest, SetEngineTorqueTest)
{
    transmission_.SetEngineTorque(300.0);

    EXPECT_DOUBLE_EQ(transmission_.engine_torque_, 300.0);
}

TEST_F(TransmissionTest, SetEngineTorqueNextGearTest)
{
    transmission_.SetEngineTorqueNextGear(300.0);

    EXPECT_DOUBLE_EQ(transmission_.engine_torque_next_gear_, 300.0);
}

TEST_F(TransmissionTest, SetWheelSpeedTest)
{
    transmission_.SetWheelSpeed(5000 / 4.77 / 4.0);

    EXPECT_NEAR(transmission_.wheel_speed_, 262.055, 0.01);
}

TEST_F(TransmissionTest, CalculateWheelTorqueTest)
{
    transmission_.SetEngineTorque(300);

    EXPECT_NEAR(transmission_.CalculateWheelTorque(), 4865.4, 0.01);
}

TEST_F(TransmissionTest, CalculateEngineSpeedTest)
{
    transmission_.SetWheelSpeed(5000 / 4.77 / 4.0);

    EXPECT_EQ(transmission_.CalculateEngineSpeed(), 5000);
}

TEST_F(TransmissionTest, SelectGearTest)
{
    transmission_.SelectGear();

    EXPECT_EQ(transmission_.current_transmission_gear_, 1);

    transmission_.SetWheelSpeed(9100 / 4.77 / 4.0);
    transmission_.SelectGear();

    EXPECT_EQ(transmission_.current_transmission_gear_, 2);

    transmission_.SetWheelSpeed(9100 / 4.77 / 0.8);
    transmission_.current_transmission_gear_ = transmission_.transmission_gear_ratios_.size();
    transmission_.SelectGear();

    EXPECT_EQ(transmission_.current_transmission_gear_, transmission_.transmission_gear_ratios_.size());
}

#ifndef _MSC_VER

TEST_F(TransmissionTest, CalculateWheelTorqueNextGearTest)
{
    transmission_.SetEngineTorque(250);
    transmission_.SetEngineTorqueNextGear(300);

    EXPECT_NEAR(transmission_.CalculateWheelTorqueNextGear(), 3649.05, 0.01);

    transmission_.current_transmission_gear_ = transmission_.transmission_gear_ratios_.size();

    EXPECT_NEAR(transmission_.CalculateWheelTorqueNextGear(), 4054.50, 0.01);
}

#endif

} // namespace
