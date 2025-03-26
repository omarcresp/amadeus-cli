#include <CLI/CLI.hpp>
#include <memory>
#include <print>
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
            std::println("{}", amadeus::VERSION);
            std::exit(0);
        },
        "Print version information and exit");

    amadeus::CliOptions options = amadeus::CliValidator::configure_cli_options(app);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }

    std::unique_ptr<amadeus::DataHandler> handler(amadeus::DataHandler::createHandler(options.file_path));

    if (!handler) {
        return 1;
    }

    if (options.print_avg) {
        handler->printAvg();
    }

    if (options.print_highest) {
        handler->printMax();
    }

    if (handler->sortWrite(options.output_path)) {
        std::println(stderr, "Failed to write output to: {}", options.output_path);

        return 1;
    }

    return 0;
}
