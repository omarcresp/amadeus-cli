#include "amadeus/data_handlers/DataHandler.hpp"

#include <filesystem>
#include <iostream>

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
        return new amadeus::XmlDataHandler(path);
    }

    if (extension == "json") {
        return new amadeus::JsonDataHandler(path);
    }

    std::cerr << "Unsupported file type: " << extension << std::endl;

    return nullptr;
}

}  // namespace amadeus
