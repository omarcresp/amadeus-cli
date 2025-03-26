#include "amadeus/data_handlers/DataHandler.hpp"

#include <filesystem>
#include <print>

#include "amadeus/data_handlers/JsonDataHandler.hpp"
#include "amadeus/data_handlers/XmlDataHandler.hpp"

namespace amadeus {

DataHandler* DataHandler::createHandler(const std::string& filePath) {
    std::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    if (!extension.empty() && extension[0] == '.') {
        extension = extension.substr(1);
    }

    if (extension == "xml") {
        return new XmlDataHandler(path);
    }

    if (extension == "json") {
        return new JsonDataHandler(path);
    }

    std::println(stderr, "Unsupported file type: {}", extension);

    return nullptr;
}

}  // namespace amadeus
