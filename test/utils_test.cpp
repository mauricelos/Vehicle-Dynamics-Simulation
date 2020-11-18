#include <array>
#include <fstream>

#include "gtest/gtest.h"

#include "utils.h"

namespace
{

class UtilsTest : public ::testing::Test
{
  public:
    std::array<char*, 1> temp_args_no_file_paths_{"program_file_name"};
    std::array<char*, 3> temp_args_{"program_file_name", "path_one", "path_two"};
    std::array<char*, 4> temp_args_race_{"program_file_name", "-r", "path_one", "path_two"};
    char* args_no_file_paths_[1] = {temp_args_no_file_paths_[0]};
    char* args_[3] = {temp_args_[0], temp_args_[1], temp_args_[2]};
    char* args_race_[4] = {temp_args_race_[0], temp_args_race_[1], temp_args_race_[2], temp_args_race_[3]};

    void SetUp()
    {
        std::ofstream("specs.yaml").put('t');
    }

    void TearDown()
    {
        std::remove("specs.yaml");
    }
};

TEST_F(UtilsTest, GetVehicleSpecificationPathsTest)
{
    auto specification_paths{Utils::GetVehicleSpecificationPaths(temp_args_.size(), args_)};
    EXPECT_EQ(specification_paths[0], "path_one");
    EXPECT_EQ(specification_paths[1], "path_two");

    specification_paths = Utils::GetVehicleSpecificationPaths(temp_args_race_.size(), args_race_);
    EXPECT_EQ(specification_paths[0], "path_one");
    EXPECT_EQ(specification_paths[1], "path_two");

    specification_paths = Utils::GetVehicleSpecificationPaths(temp_args_no_file_paths_.size(), args_no_file_paths_);
    EXPECT_TRUE(specification_paths[0].rfind("specs.yaml") != std::string::npos);
}

TEST_F(UtilsTest, GetYamlFilesFromCurrentDirectoryTest)
{
    std::ofstream("specs.json").put('t');
    auto specification_paths{Utils::GetYamlFilesFromCurrentDirectory()};
    std::remove("specs.json");

    EXPECT_TRUE(specification_paths[0].rfind("specs.yaml") != std::string::npos);
    EXPECT_EQ(specification_paths.size(), 1);
}

TEST_F(UtilsTest, HasRaceCommandLineOptionTest)
{
    std::array<char*, 4> temp_alt_args_race{"program_file_name", "--race", "path_one", "path_two"};
    char* alt_args_race[4] = {temp_alt_args_race[0], temp_alt_args_race[1], temp_alt_args_race[2],
                              temp_alt_args_race[3]};

    EXPECT_TRUE(Utils::HasRaceCommandLineOption(temp_args_race_.size(), args_race_));
    EXPECT_TRUE(Utils::HasRaceCommandLineOption(temp_alt_args_race.size(), alt_args_race));
    EXPECT_FALSE(Utils::HasRaceCommandLineOption(temp_args_.size(), args_));
}

} // namespace