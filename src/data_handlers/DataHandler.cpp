#include "amadeus/data_handlers/DataHandler.hpp"

#include <filesystem>
#include <iostream>

#include "amadeus/data_handlers/JsonDataHandler.hpp"
#include "amadeus/data_handlers/XmlDataHandler.hpp"

namespace amadeus {

DataHandler* DataHandler::createHandler(const std::string& filePath) {
    std::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    // Remove leading dot from extension if present
    if (!extension.empty() && extension[0] == '.') {
        extension = extension.substr(1);
    }

    if (extension == "xml") {
        return new XmlDataHandler();
    } else if (extension == "json") {
        return new JsonDataHandler();
    } else {
        std::cerr << "Unsupported file type: " << extension << std::endl;
        return nullptr;
    }
}

}  // namespace amadeus