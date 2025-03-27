#include <gtest/gtest.h>

#include <CLI/CLI.hpp>

#include "amadeus/Version.h"

TEST(VersionTest, VersionFormat) {
    std::string version = amadeus::VERSION;

    int dot_count = 0;
    for (char c : version) {
        if (c == '.') {
            dot_count++;
        }
    }

    EXPECT_GE(dot_count, 2);
}
