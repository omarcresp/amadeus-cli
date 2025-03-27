#include "amadeus/data_handlers/DataHandler.hpp"

#include <filesystem>
#include <memory>
#include <print>

#include "amadeus/data_handlers/JsonDataHandler.hpp"
#include "amadeus/data_handlers/XmlDataHandler.hpp"

using std::string;

namespace amadeus {

std::expected<std::unique_ptr<DataHandler>, string> DataHandler::createHandler(const string& filePath) {
    std::filesystem::path path(filePath);
    string extension = path.extension().string();

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
