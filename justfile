# Amadeus CLI justfile

# List available commands
default:
    @just --list

# Build the project
build:
    cmake -B build
    cmake --build build

# Run the CLI
run:
    ./build/bin/amadeus-cli

# Run with version flag
version:
    ./build/bin/amadeus-cli -v

# Run tests
test:
    ctest --test-dir build --output-on-failure

# Format code
format:
    clang-format -i -style=file $(find src include test -name "*.cpp" -o -name "*.h" -o -name "*.hpp")

# Check code formatting
format-check:
    clang-format -n -Werror -style=file $(find src include test -name "*.cpp" -o -name "*.h" -o -name "*.hpp")

# Install pre-commit hooks
hooks:
    pre-commit install

# Clean build artifacts
clean:
    rm -rf build/ 