///
/// @file vehicle_specification_parser.h
///

#ifndef VEHICLE_SPECIFICATION_PARSER_H
#define VEHICLE_SPECIFICATION_PARSER_H

#include <string>

class Vehicle;

class VehicleSpecificationParser final
{
  public:
    static Vehicle ParseVehicleSpecification(const std::string& spec_file_path);
};

#endif // VEHICLE_SPECIFICATION_PARSER_H
