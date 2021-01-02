#include "yaml-cpp/yaml.h"
#include "gtest/gtest.h"

#include "vehicle.h"
#include "vehicle_specification_parser.h"

namespace
{

class VehicleSpecificationParserTest : public ::testing::Test
{
  public:
    std::string yaml_file_path_{"vehicle_specifications/mazda_rx8_8HP70.yaml"};
    std::string non_existing_path_{"vehicle_specifications/non_existing.yaml"};
    std::string wrong_format_file_path_{"vehicle_specifications/wrong_format.yaml"};
};

TEST_F(VehicleSpecificationParserTest, ParseVehicleSpecificationCorrectFile)
{
    auto vehicle = VehicleSpecificationParser::ParseVehicleSpecification(yaml_file_path_);

    EXPECT_EQ(vehicle.GetVehicleName(), "Mazda RX-8 R3 8HP70");
    EXPECT_EQ(vehicle.GetEngine().GetMaxEngineSpeed(), 9250);
    EXPECT_DOUBLE_EQ(vehicle.GetEngine().GetTorqueAtEngineSpeed(1000), 97.0);
    EXPECT_DOUBLE_EQ(vehicle.GetEngine().GetTorqueAtEngineSpeed(6000), 215.4);
    EXPECT_DOUBLE_EQ(vehicle.GetTransmission().GetEngineSpeedNextGear(), 0.0);
    EXPECT_DOUBLE_EQ(vehicle.GetVehicleModel().GetDeltaTime(), 0.01);
    EXPECT_DOUBLE_EQ(vehicle.GetVehicleModel().GetVehicleDrivenDistance(), 0.0);
    EXPECT_DOUBLE_EQ(vehicle.GetVehicleModel().GetVehicleAcceleration(), 0.0);
    EXPECT_DOUBLE_EQ(vehicle.GetVehicleModel().GetVehicleSpeed(), 0.0);
}

TEST_F(VehicleSpecificationParserTest, ParseVehicleSpecificationNonExistingFile)
{
    const std::string exception_error{"bad file: " + non_existing_path_};

    EXPECT_THROW(
        {
            try
            {
                auto vehicle = VehicleSpecificationParser::ParseVehicleSpecification(non_existing_path_);
            }
            catch (const YAML::BadFile& error)
            {
                EXPECT_STREQ(exception_error.c_str(), error.what());
                throw;
            }
        },
        YAML::BadFile);
}

TEST_F(VehicleSpecificationParserTest, ParseVehicleSpecificationWrongFormatFile)
{
    const std::string exception_error{"bad conversion"};

    EXPECT_THROW(
        {
            try
            {
                auto vehicle = VehicleSpecificationParser::ParseVehicleSpecification(wrong_format_file_path_);
            }
            catch (const YAML::BadConversion& error)
            {
                EXPECT_STREQ(exception_error.c_str(), error.what());
                throw;
            }
        },
        YAML::BadConversion);
}

} // namespace