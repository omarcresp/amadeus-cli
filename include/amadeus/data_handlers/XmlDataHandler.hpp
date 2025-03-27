#pragma once

#include <expected>
#include <memory>
#include <pugixml.hpp>
#include <string>
#include <vector>

#include "amadeus/Employee.hpp"
#include "amadeus/data_handlers/DataHandler.hpp"

using std::string;

namespace amadeus {

class XmlDataHandler : public DataHandler {
public:
    ~XmlDataHandler() override;

    [[nodiscard]] std::expected<void, string> sortWrite(const string& outputPath) override;

    void printMax() override;

    void printAvg() override;

    [[nodiscard]] static std::expected<std::unique_ptr<DataHandler>, string> create(const string& filePath);

private:
    explicit XmlDataHandler(const pugi::xml_document& doc);

    std::vector<Employee> m_employees;
    double m_totalSalaries;
    Employee m_highestIncome;
};

}  // namespace amadeus
