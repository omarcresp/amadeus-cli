add_executable(amadeus-cli
    main.cpp
)

target_include_directories(amadeus-cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(amadeus-cli PRIVATE CLI11::CLI11)

# Set output directory
set_target_properties(amadeus-cli PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
) 