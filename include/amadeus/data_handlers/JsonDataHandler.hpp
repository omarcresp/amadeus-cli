#include <expected>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "amadeus/Employee.hpp"
#include "amadeus/data_handlers/DataHandler.hpp"

using std::string;

namespace amadeus {

class JsonDataHandler : public DataHandler {
public:
    ~JsonDataHandler() override;

    [[nodiscard]] static std::expected<std::unique_ptr<DataHandler>, string> create(const string& filePath);

    [[nodiscard]] std::expected<void, string> sortWrite(const string& outputPath) override;

    void printMax() override;

    void printAvg() override;

private:
    explicit JsonDataHandler(const nlohmann::json& jsonData);

    std::vector<Employee> m_employees;
    double m_totalSalaries;
    Employee m_highestIncome;
};

}  // namespace amadeus
