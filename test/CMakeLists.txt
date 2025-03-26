include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(cli_test
    cli_test.cpp
)

target_link_libraries(cli_test
    PRIVATE
    gtest_main
    CLI11::CLI11
)

include(GoogleTest)
gtest_discover_tests(cli_test) 