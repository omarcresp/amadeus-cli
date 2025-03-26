#pragma once

#include <string>
#include <vector>

#include "amadeus/Employee.hpp"

namespace amadeus {

class DataHandler {
public:
    virtual ~DataHandler() = default;

    virtual int sortWrite(const std::string& outputPath) = 0;

    virtual void printMax() = 0;

    virtual void printAvg() = 0;

    static DataHandler* createHandler(const std::string& filePath);
};

}  // namespace amadeus
