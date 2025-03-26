#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

#include "amadeus/CliOptions.hpp"
#include "amadeus/Version.h"

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

    // Default action
    std::cout << "Input file: " << options.file_path << std::endl;
    std::cout << "Output file: " << options.output_path << std::endl;
    std::cout << "Output format: " << options.output_format << std::endl;

    return 0;
}
