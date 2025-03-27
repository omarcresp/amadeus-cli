cmake_minimum_required(VERSION 3.14)

# Enable compile_commands.json generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include custom modules
include(cmake/GitVersion.cmake)

# Version handling
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# Try to get version from git if available
get_git_version()
if(DEFINED GIT_VERSION_FOUND AND GIT_VERSION_FOUND)
    set(VERSION "${GIT_VERSION}")
    set(VERSION_MAJOR "${GIT_VERSION_MAJOR}")
    set(VERSION_MINOR "${GIT_VERSION_MINOR}")
    set(VERSION_PATCH "${GIT_VERSION_PATCH}")
endif()

project(amadeus-cli VERSION ${VERSION} LANGUAGES CXX)
message(STATUS "Configuring ${PROJECT_NAME} v${PROJECT_VERSION}")

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compile options
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
endif()

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find required packages
find_package(CLI11 CONFIG)
if(NOT CLI11_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG v2.5.0
    )
    FetchContent_MakeAvailable(cli11)
endif()

# Add nlohmann/json
find_package(nlohmann_json 3.11.3 CONFIG)
if(NOT nlohmann_json_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

# Add pugixml
find_package(pugixml 1.15 CONFIG)
if(NOT pugixml_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml.git
        GIT_TAG v1.15
    )
    FetchContent_MakeAvailable(pugixml)
endif()

# Set up versioning - create version header from template
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/amadeus/Version.h
    @ONLY
)

# Add subdirectories
add_subdirectory(src)

# Testing setup
option(BUILD_TESTS "Build the tests" ON)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# Installation
install(TARGETS amadeus-cli
    RUNTIME DESTINATION bin
)
