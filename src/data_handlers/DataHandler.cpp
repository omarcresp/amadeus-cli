#include "amadeus/data_handlers/DataHandler.hpp"

#include <filesystem>
#include <memory>
#include <print>

#include "amadeus/data_handlers/JsonDataHandler.hpp"
#include "amadeus/data_handlers/XmlDataHandler.hpp"

namespace amadeus {

std::expected<std::unique_ptr<DataHandler>, std::string> DataHandler::createHandler(const std::string& filePath) {
    std::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    if (!extension.empty() && extension[0] == '.') {
        extension = extension.substr(1);
    }

    if (extension == "xml") {
        return XmlDataHandler::create(path.string());
    }

    if (extension == "json") {
        return JsonDataHandler::create(path.string());
    }

    return std::unexpected("Unsupported file type: " + extension);
}

}  // namespace amadeus
