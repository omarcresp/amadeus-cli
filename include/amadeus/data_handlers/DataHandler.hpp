#pragma once

#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "amadeus/Employee.hpp"

namespace amadeus {

class DataHandler {
public:
    virtual ~DataHandler() = default;

    [[nodiscard]] virtual std::expected<void, std::string> sortWrite(const std::string& outputPath) = 0;

    virtual void printMax() = 0;

    virtual void printAvg() = 0;

    [[nodiscard]] static std::expected<std::unique_ptr<DataHandler>, std::string> createHandler(
        const std::string& filePath);
};

}  // namespace amadeus
