#include "amadeus/data_handlers/XmlDataHandler.hpp"

#include <expected>
#include <memory>
#include <print>
#include <pugixml.hpp>
#include <string>

using std::string;

namespace amadeus {

std::expected<std::unique_ptr<DataHandler>, string> XmlDataHandler::create(const string& filePath) {
    try {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(filePath.c_str());

        if (!result) {
            return std::unexpected(string("Error parsing XML file: ") + result.description());
        }

        if (doc.child("employees").empty()) {
            return std::unexpected(string("Error: Missing employees in file: "));
        }

        if (doc.child("employees").first_child().child("salary").empty()) {
            return std::unexpected(string("Error: Missing employe salary in file: "));
        }

        return std::unique_ptr<DataHandler>(new XmlDataHandler(doc));
    } catch (const std::exception& e) {
        return std::unexpected(string("Error creating XmlDataHandler: ") + e.what());
    }
}

XmlDataHandler::XmlDataHandler(const pugi::xml_document& doc) {
    auto employeesList = doc.child("employees");

    m_employees = {};
    m_totalSalaries = 0;
    m_highestIncome.salary = 0;

    for (pugi::xml_node employee = employeesList.first_child(); employee; employee = employee.next_sibling()) {
        auto name = employee.child("name").child_value();
        auto id = std::stoi(employee.child("id").child_value());
        auto department = employee.child("department").child_value();
        auto salary = std::stod(employee.child("salary").child_value());

        Employee item(name, id, department, salary);

        m_employees.push_back(item);
        m_totalSalaries += salary;

        if (salary > m_highestIncome.salary) {
            m_highestIncome = item;
        }
    }
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
