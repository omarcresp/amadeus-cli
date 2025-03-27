#include "amadeus/data_handlers/XmlDataHandler.hpp"

#include <expected>
#include <memory>
#include <print>
#include <pugixml.hpp>

using std::string;

namespace amadeus {

std::expected<std::unique_ptr<DataHandler>, string> XmlDataHandler::create(const string& filePath) {
    try {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(filePath.c_str());

        if (!result) {
            std::println("XML parse error: {}", result.description());
        }

        return std::unique_ptr<DataHandler>(new XmlDataHandler(doc));
    } catch (const std::exception& e) {
        return std::unexpected(string("Error creating XmlDataHandler: ") + e.what());
    }
}

XmlDataHandler::XmlDataHandler(const pugi::xml_document& doc) {
    (void)doc;

    m_employees = {Employee{"John Doe", 1, "Engineering", 75000.0}, Employee{"Jane Smith", 2, "HR", 65000.0},
                   Employee{"Bob Wilson", 3, "Marketing", 70000.0}};
    m_totalSalaries = 210000.0;
    m_highestIncome = m_employees[0];
}

XmlDataHandler::~XmlDataHandler() {}

std::expected<void, string> XmlDataHandler::sortWrite(const string& outputPath) {
    if (outputPath.empty()) {
        return std::unexpected("Error: outputPath is empty");
    }

    std::println("\nXML handler - sortWrite: pending to implement");
    std::print("Output path: {}", outputPath);

    return {};
}

void XmlDataHandler::printMax() {
    std::println("Higher income employee");
    std::println("ID: {}", m_highestIncome.id);
    std::println("Name: {}", m_highestIncome.name);
    std::println("Department: {}", m_highestIncome.department);
    std::println("Salary: {}", m_highestIncome.salary);
}

void XmlDataHandler::printAvg() {
    double avgSalary = m_totalSalaries / m_employees.size();
    std::println("Average salary: {}\n", avgSalary);
}

}  // namespace amadeus
