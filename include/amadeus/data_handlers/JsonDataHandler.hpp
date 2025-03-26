#pragma once

#include <string>
#include <vector>

#include "amadeus/Employee.hpp"
#include "amadeus/data_handlers/DataHandler.hpp"

namespace amadeus {

class JsonDataHandler : public DataHandler {
public:
    explicit JsonDataHandler(const std::string& filePath);
    ~JsonDataHandler() override;

    int sortWrite(const std::string& outputPath) override;

    int printMax() override;

    int printAvg() override;

private:
    std::vector<Employee> m_employees;
};

}  // namespace amadeus
