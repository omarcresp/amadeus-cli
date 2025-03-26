#pragma once

#include <CLI/CLI.hpp>
#include <filesystem>
#include <string>
#include <vector>

#include "amadeus/Constants.hpp"

namespace amadeus {

struct CliOptions {
    std::string file_path;
    std::string output_path;
    std::string output_format;
    bool print_avg = false;
    bool print_highest = false;
};

class CliValidator {
public:
    static CliOptions configure_cli_options(CLI::App& app) {
        CliOptions options;

        app.add_option("file", options.file_path,
                       "Accepted formats: " + amadeus::join_formats(amadeus::ALLOWED_FILE_FORMATS))
            ->required()
            ->check(CLI::ExistingFile);

        app.add_option("-o,--output", options.output_path, "Output file path")->check(ValidPath);

        app.add_option(
               "-f,--format", options.output_format,
               "Output format (" + amadeus::join_formats(amadeus::ALLOWED_FILE_FORMATS) + ")")
            ->check(CLI::IsMember(amadeus::ALLOWED_FILE_FORMATS));

        app.add_flag("-a,--average", options.print_avg, "Print average salary to stdout");
        app.add_flag("-m,--max", options.print_highest,
                     "Print highest paid employee details to stdout");

        return options;
    }

private:
    static const CLI::Validator ValidPath;
};

const CLI::Validator CliValidator::ValidPath = CLI::Validator(
    [](const std::string& path) -> std::string {
        if (!std::filesystem::exists(std::filesystem::path(path).parent_path())) {
            return "Parent directory does not exist";
        }
        return "";
    },
    "Path");

}  // namespace amadeus
