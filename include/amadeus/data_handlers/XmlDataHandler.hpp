#pragma once

#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "amadeus/Employee.hpp"
#include "amadeus/data_handlers/DataHandler.hpp"

namespace amadeus {

class XmlDataHandler : public DataHandler {
public:
    ~XmlDataHandler() override;

    [[nodiscard]] std::expected<void, std::string> sortWrite(const std::string& outputPath) override;

    void printMax() override;

    void printAvg() override;

    // Static factory method that returns std::expected
    [[nodiscard]] static std::expected<std::unique_ptr<DataHandler>, std::string> create(const std::string& filePath);

private:
    // Private constructor to enforce factory method
    explicit XmlDataHandler(const std::string& filePath);

    std::vector<Employee> m_employees;
    double m_totalSalaries;
    Employee m_highestIncome;
};

}  // namespace amadeus
