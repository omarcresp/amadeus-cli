#pragma once

#include <string>
#include <vector>

#include "amadeus/Employee.hpp"

namespace amadeus {

class DataHandler {
public:
    virtual ~DataHandler() = default;

    // Sort employees by ID and write to output file
    virtual bool sortWrite(const std::string& outputPath) = 0;

    // Print highest paid employee
    virtual void printMax() = 0;

    // Print average salary
    virtual void printAvg() = 0;

    // Get employees data
    virtual const std::vector<Employee>& getEmployees() const = 0;

    // Create the appropriate data handler based on file extension
    static DataHandler* createHandler(const std::string& filePath);
};

}  // namespace amadeus