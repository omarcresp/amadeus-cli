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

    auto handlerResult = amadeus::DataHandler::createHandler(options.file_path);

    if (!handlerResult) {
        std::println(stderr, "Error: {}", handlerResult.error());
        return 1;
    }

    auto& handler = handlerResult.value();

    auto writeResult = handler->sortWrite(options.output_path);

    if (!writeResult) {
        std::println(stderr, "{}", writeResult.error());
        return 1;
    }

    if (options.print_avg) {
        handler->printAvg();
    }

    if (options.print_highest) {
        handler->printMax();
    }

    std::print("Amadeus CLI - Wrote sorted employees to: {}", options.output_path);

    return 0;
}
