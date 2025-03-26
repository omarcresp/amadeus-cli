# Amadeus CLI

A robust CLI tool framework for internal use.

## Quick Start with Nix (Recommended)

The recommended way to build and develop this project is using Nix, which ensures reproducible builds and consistent development environments.

### Requirements for Nix Setup
- Nix package manager with flakes enabled
- Linux operating system

### Nix Commands
```bash
# Build the production binary
nix build

# Run the cli directly
nix run

# Run tests
nix run .#test

# Enter development shell
nix shell
```

### Using direnv with Nix (Optional)
If you have direnv installed, the development environment will be automatically loaded when you enter the project directory:
```bash
direnv allow
```

## Traditional Linux Setup (Without Nix)

If you prefer not to use Nix, you can build and run the project directly. This method requires manual installation of dependencies.

### Requirements
- CMake 3.14 or higher
- C++17 compatible compiler
- CLI11 library
- Google Test framework (for testing)
- Linux operating system
- clang-format (for code formatting)

### Installing Dependencies
#### Ubuntu/Debian
```bash
sudo apt update
sudo apt install cmake build-essential libcli11-dev libgtest-dev clang-format
```

#### Fedora
```bash
sudo dnf install cmake gcc-c++ cli11-devel gtest-devel clang-tools-extra
```

#### Arch Linux
```bash
sudo pacman -S cmake base-devel cli11 gtest clang
```

### Building from Source
```bash
# Configure the project
cmake -B build

# Build the project
cmake --build build
```

### Running
After building, the binary will be located in `build/bin/amadeus-cli`:
```bash
./build/bin/amadeus-cli -v
```

### Testing
Run all tests
```bash
ctest --test-dir build --output-on-failure
```

## Development

### Code Formatting

This project uses clang-format for consistent code style. A configuration file (.clang-format) based on Google's C++ style guide with small modifications is included in the repository.

### Format Code
```bash
# Using Nix (recommended)
nix run .#format

# Using clang-format directly
clang-format -i -style=file $(find src include test -name "*.cpp" -o -name "*.h" -o -name "*.hpp")
```

### Check Format
```bash
# Using Nix (recommended)
nix run .#format-check

# Using clang-format directly
clang-format -n -Werror -style=file $(find src include test -name "*.cpp" -o -name "*.h" -o -name "*.hpp")
```

### Pre-commit Hooks
The project is configured with pre-commit hooks to ensure code is properly formatted before committing:
```bash
# Install pre-commit hooks (done automatically in nix shell)
pre-commit install
```

### Project Structure
- `include/` - Header files
- `src/` - Source files
- `test/` - Test files
- `cmake/` - CMake configuration files

## Troubleshooting

### Common Issues with Nix
- If flakes are not enabled, add `experimental-features = nix-command flakes` to your `/etc/nix/nix.conf`
- If you see "command not found: direnv", install it via your system package manager

### Common Issues without Nix
- Missing dependencies: Ensure all required libraries are installed
- CMake version too old: Update CMake to 3.14 or higher
- Build errors: Make sure you have a C++17 compatible compiler 