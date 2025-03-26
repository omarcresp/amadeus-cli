#pragma once

#include <CLI/CLI.hpp>
#include <filesystem>
#include <string>
#include <vector>

#include "amadeus/Constants.hpp"

using string = std::string;

namespace amadeus {

struct CliOptions {
    string file_path;
    string output_path;
    string output_format;
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

        app.add_flag("-a,--average", options.print_avg, "Print average salary to stdout");
        app.add_flag("-m,--max", options.print_highest, "Print highest paid employee details to stdout");

        app.callback([&options]() {
            if (options.output_path.empty()) {
                options.output_path = get_default_output_path(options.file_path);
            }
        });

        return options;
    }

private:
    static const CLI::Validator ValidPath;
    static const string get_default_output_path(const string& file_path);
};

inline const string CliValidator::get_default_output_path(const string& file_path) {
    std::filesystem::path input_path(file_path);

    return (input_path.parent_path() / (input_path.stem().string() + ".result" + input_path.extension().string()))
        .string();
}

inline const CLI::Validator CliValidator::ValidPath = CLI::Validator(
    [](const string& path) -> string {
        if (!std::filesystem::exists(std::filesystem::path(path).parent_path())) {
            return "Parent directory does not exist";
        }
        return "";
    },
    "Path");

}  // namespace amadeus
