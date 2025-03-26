#include <CLI/CLI.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "amadeus/CliOptions.hpp"
#include "amadeus/Version.h"
#include "amadeus/data_handlers/DataHandler.hpp"

using std::string;

int main(int argc, char** argv) {
    CLI::App app{"Amadeus CLI Tool\nAnalyzes employees datasource to output data analysis\n"};

    app.add_flag_function(
        "-v,--version",
        [](int) {
            std::cout << amadeus::VERSION << std::endl;
            std::exit(0);
        },
        "Print version information and exit");

    amadeus::CliOptions options = amadeus::CliValidator::configure_cli_options(app);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }

    // Create appropriate data handler based on input file
    std::unique_ptr<amadeus::DataHandler> handler(
        amadeus::DataHandler::createHandler(options.file_path));

    if (!handler) {
        std::cerr << "Failed to create data handler for file: " << options.file_path << std::endl;
        return 1;
    }

    // Initialize handler with input file
    if (!handler->initialize(options.file_path)) {
        std::cerr << "Failed to initialize data handler with file: " << options.file_path
                  << std::endl;
        return 1;
    }

    // Process according to options
    if (options.print_avg) {
        handler->printAvg();
    }

    if (options.print_highest) {
        handler->printMax();
    }

    // Write sorted output if output path is specified
    if (!options.output_path.empty()) {
        if (!handler->sortWrite(options.output_path)) {
            std::cerr << "Failed to write output to: " << options.output_path << std::endl;
            return 1;
        }
    }

    return 0;
}
