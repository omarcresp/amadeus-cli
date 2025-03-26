#include <gtest/gtest.h>

#include <CLI/CLI.hpp>

#include "amadeus/Version.h"

TEST(VersionTest, VersionFormat) {
    std::string version = amadeus::VERSION;
    // Check if it contains at least two dots (major.minor.patch)
    int dot_count = 0;
    for (char c : version) {
        if (c == '.') {
            dot_count++;
        }
    }
    EXPECT_GE(dot_count, 2);
}

// Add more tests as needed