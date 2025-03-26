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

    int sortWrite(const std::string& outputPath) override;

    int printMax() override;

    int printAvg() override;

private:
    std::vector<Employee> m_employees;
};

}  // namespace amadeus
