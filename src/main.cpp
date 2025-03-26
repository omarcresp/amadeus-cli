#include "amadeus/Version.h"
#include <CLI/CLI.hpp>
#include <iostream>

int main(int argc, char **argv) {
  CLI::App app{"Amadeus CLI Tool"};

  bool show_version = false;
  app.add_flag("-v,--version", show_version,
               "Print version information and exit");

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }

  if (show_version) {
    std::cout << amadeus::VERSION << std::endl;
    return 0;
  }

  // Default action
  std::cout << "Hello, World!" << std::endl;

  return 0;
}
