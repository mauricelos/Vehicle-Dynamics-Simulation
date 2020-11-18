///
/// @file utils.h
///

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils
{
  public:
    static std::vector<std::string> GetVehicleSpecificationPaths(const int argc, char** argv);
    static std::vector<std::string> GetYamlFilesFromCurrentDirectory();
    static bool HasRaceCommandLineOption(const int argc, char** argv);

  private:
    static constexpr char yaml_suffix_[6]{".yaml"};
};

#endif // UTILS_H