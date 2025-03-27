#pragma once

#include <string>

using std::string;

namespace amadeus {

// New simple struct version
struct Employee {
    string name;
    int id;
    string department;
    double salary;
};

}  // namespace amadeus