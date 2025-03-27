#pragma once

#include <expected>
#include <memory>
#include <pugixml.hpp>
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

    [[nodiscard]] static std::expected<std::unique_ptr<DataHandler>, std::string> create(const std::string& filePath);

private:
    explicit XmlDataHandler(const pugi::xml_document& doc);

    std::vector<Employee> m_employees;
    double m_totalSalaries;
    Employee m_highestIncome;
};

}  // namespace amadeus
