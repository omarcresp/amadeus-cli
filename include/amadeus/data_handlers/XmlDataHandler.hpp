#pragma once

#include <string>
#include <vector>

#include "amadeus/Employee.hpp"
#include "amadeus/data_handlers/DataHandler.hpp"

namespace amadeus {

class XmlDataHandler : public DataHandler {
public:
    explicit XmlDataHandler(const std::string& filePath);
    ~XmlDataHandler() override;

    // Sort employees by ID and write to output file
    bool sortWrite(const std::string& outputPath) override;

    // Print highest paid employee
    void printMax() override;

    // Print average salary
    void printAvg() override;

    // Get employees data
    const std::vector<Employee>& getEmployees() const override;

private:
    std::vector<Employee> m_employees;
};

}  // namespace amadeus