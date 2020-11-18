#include "gtest/gtest.h"

#define private public
#include "engine.h"
#undef private

namespace
{

class EngineTest : public ::testing::Test
{
};

TEST_F(EngineTest, EngineConstructorTestNormal)
{
    Engine engine{1000, 7500, {{1000.0, 5000.0, 7500.0}, {100.0, 300.0, 500.0}}};

    EXPECT_EQ(engine.GetMaxEngineSpeed(), 7500);
    EXPECT_DOUBLE_EQ(engine.GetTorqueAtEngineSpeed(1000.0), 100.0);
    EXPECT_DOUBLE_EQ(engine.GetTorqueAtEngineSpeed(5000.0), 300.0);

    engine.SetEngineSpeed(5000);

    EXPECT_DOUBLE_EQ(engine.CalculateEngineTorque(), 300.0);
    EXPECT_NEAR(engine.CalculateEngineHorsePower(), 213.496, 0.01);
}

TEST_F(EngineTest, EngineConstructorTestTooFewEngineTorquePerRpmPoints)
{
    ASSERT_DEATH({ Engine engine(1000, 7500, {{1000.0, 7500.0}, {100.0, 500.0}}); }, "");
}

TEST_F(EngineTest, EngineConstructorTestSwitchedMaxAndMinRPM)
{
    Engine engine{7500, 1000, {{1000.0, 5000.0, 7500.0}, {100.0, 300.0, 500.0}}};

    EXPECT_EQ(engine.GetMaxEngineSpeed(), 7500);
    EXPECT_DOUBLE_EQ(engine.GetTorqueAtEngineSpeed(1000.0), 100.0);
    EXPECT_DOUBLE_EQ(engine.GetTorqueAtEngineSpeed(5000.0), 300.0);

    engine.SetEngineSpeed(5000);

    EXPECT_DOUBLE_EQ(engine.CalculateEngineTorque(), 300.0);
    EXPECT_NEAR(engine.CalculateEngineHorsePower(), 213.496, 0.01);
}

TEST_F(EngineTest, EngineConstructorTestSameRPM)
{
    Engine engine{1000, 1000, {{1000.0, 5000.0, 7500.0}, {100.0, 300.0, 500.0}}};

    EXPECT_EQ(engine.GetMaxEngineSpeed(), 1000);
    EXPECT_DOUBLE_EQ(engine.GetTorqueAtEngineSpeed(1000.0), 100.0);
    EXPECT_DOUBLE_EQ(engine.GetTorqueAtEngineSpeed(5000.0), 300.0);

    engine.SetEngineSpeed(5000);

    EXPECT_DOUBLE_EQ(engine.CalculateEngineTorque(), 0.0);
    EXPECT_DOUBLE_EQ(engine.CalculateEngineHorsePower(), 0.0);
}

TEST_F(EngineTest, EngineSetEngineSpeedBoundriesTest)
{
    Engine engine{1000, 9000, {{1000.0, 5000.0, 7500.0}, {100.0, 300.0, 500.0}}};
    engine.SetEngineSpeed(10000);

    EXPECT_EQ(engine.engine_rpm_, 10000);
    EXPECT_DOUBLE_EQ(engine.CalculateEngineTorque(), 0.0);

    engine.SetEngineSpeed(-1000);

    EXPECT_EQ(engine.engine_rpm_, 64536);
    EXPECT_DOUBLE_EQ(engine.CalculateEngineTorque(), 0.0);

    engine.SetEngineSpeed(0);

    EXPECT_EQ(engine.engine_rpm_, 0);
    EXPECT_DOUBLE_EQ(engine.CalculateEngineTorque(), 100.0);
}

TEST_F(EngineTest, EngineGetMaxEngineSpeedTest)
{
    Engine engine{1000, 9000, {{1000.0, 5000.0, 7500.0}, {100.0, 300.0, 500.0}}};

    EXPECT_EQ(engine.GetMaxEngineSpeed(), 9000);
}

TEST_F(EngineTest, EngineGetTorqueAtEngineSpeedTest)
{
    Engine engine{1000, 9000, {{1000.0, 5000.0, 7500.0}, {100.0, 300.0, 500.0}}};

    EXPECT_DOUBLE_EQ(engine.GetTorqueAtEngineSpeed(5000), 300.0);
}

} // namespace