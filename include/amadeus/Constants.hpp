#pragma once

#include <string>
#include <vector>

using std::string;

namespace amadeus {

const std::vector<string> ALLOWED_FILE_FORMATS = {"xml", "json"};

inline string join_formats(const std::vector<string>& formats) {
    string result;
    for (size_t i = 0; i < formats.size(); ++i) {
        if (i > 0)
            result += ", ";
        result += formats[i];
    }
    return result;
}

}  // namespace amadeus
