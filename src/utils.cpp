#include <algorithm>
#include <filesystem>

#include "utils.h"

#ifdef __APPLE__
#include <mach-o/dyld.h>

std::string GetMachOExecutablePath()
{
    unsigned int bufferSize = 512;
    std::vector<char> buffer(bufferSize + 1);

    if (_NSGetExecutablePath(&buffer[0], &bufferSize))
    {
        buffer.resize(bufferSize);
        _NSGetExecutablePath(&buffer[0], &bufferSize);
    }

    const std::filesystem::path path{&buffer[0]};

    return path.parent_path().string();
}
#endif

std::vector<std::string> Utils::GetVehicleSpecificationPaths(const int argc, char** argv)
{
    return argc == 1
               ? GetYamlFilesFromCurrentDirectory()
               : std::vector<std::string>{(HasRaceCommandLineOption(argc, argv) ? argv + 2 : argv + 1), argv + argc};
}

std::vector<std::string> Utils::GetYamlFilesFromCurrentDirectory()
{
    std::vector<std::string> vehicle_spec_files{};

#ifdef __APPLE__
    for (const auto& file : std::filesystem::directory_iterator(GetMachOExecutablePath()))
    {
        if (file.path().extension() == yaml_suffix_)
        {
            vehicle_spec_files.push_back(file.path().string());
        }
    }
#else
    for (const auto& file : std::filesystem::directory_iterator(std::filesystem::current_path().string()))
    {
        if (file.path().extension() == yaml_suffix_)
        {
            vehicle_spec_files.push_back(file.path().string());
        }
    }
#endif

    return vehicle_spec_files;
}

bool Utils::HasRaceCommandLineOption(const int argc, char** argv)
{
    return argc == 4 && (std::string{argv[1]} == "--race" || std::string{argv[1]} == "-r") ? true : false;
}