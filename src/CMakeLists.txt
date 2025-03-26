add_executable(amadeus-cli
    main.cpp
    Employee.cpp
    data_handlers/DataHandler.cpp
    data_handlers/XmlDataHandler.cpp
    data_handlers/JsonDataHandler.cpp
)

target_include_directories(amadeus-cli 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CLI11_INCLUDE_DIR}
)

target_link_libraries(amadeus-cli 
    PRIVATE 
    CLI11::CLI11
)

# Set output directory
set_target_properties(amadeus-cli PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
) 