#pragma once

#include <string>

namespace amadeus {

// New simple struct version
struct Employee {
    std::string name;
    int id;
    std::string department;
    double salary;
};

}  // namespace amadeus