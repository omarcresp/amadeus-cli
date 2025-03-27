#pragma once

#include <expected>
#include <memory>
#include <string>

using std::string;

namespace amadeus {

class DataHandler {
public:
    virtual ~DataHandler() = default;

    [[nodiscard]] virtual std::expected<void, string> sortWrite(const string& outputPath) = 0;

    virtual void printMax() = 0;

    virtual void printAvg() = 0;

    [[nodiscard]] static std::expected<std::unique_ptr<DataHandler>, string> createHandler(const string& filePath);
};

}  // namespace amadeus
