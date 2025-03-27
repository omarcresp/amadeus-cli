{
  description = "Amadeus CLI - A robust internal CLI tool";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        # Get version from environment or default to 0.0.1
        version = builtins.getEnv "VERSION";
        finalVersion = if version != "" then version else "0.0.1";

        # Common build inputs for both dev and prod
        commonInputs = with pkgs; [
          cmake
          ninja
          gtest
        ];

        # Development shell additional inputs
        devInputs = with pkgs; [
          clang-tools
          gdb
          valgrind
          git
          pre-commit
          just
          nodejs_22
        ];

      in {
        # Default package (production build)
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "amadeus-cli";
          version = finalVersion;
          src = ./.;

          nativeBuildInputs = commonInputs;

          configurePhase = ''
            cmake -B build -DBUILD_TESTS=OFF
          '';

          buildPhase = ''
            cmake --build build
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp build/bin/amadeus-cli $out/bin/
          '';

          meta = with pkgs.lib; {
            description = "A robust internal CLI tool";
            platforms = platforms.linux;
          };
        };

        # Development shell
        devShells.default = pkgs.mkShell {
          buildInputs = commonInputs ++ devInputs;

          shellHook = ''
            echo "Amadeus CLI Development Shell"
            echo ""
            echo "Available commands (run 'just --list' for more):"
            echo "  just build          # Configure and build the project"
            echo "  just test           # Run tests"
            echo "  just run            # Run the CLI tool"
            echo "  just format         # Format code"
            echo "  just check-format   # Check code formatting"
            echo ""

            # Setup pre-commit hooks if not already installed
            if [ -z "$(ls -A .git/hooks)" ]; then
              pre-commit install
            fi
          '';
        };

        # Apps
        apps = {
          # Default app
          default = {
            type = "app";
            program = toString (pkgs.writeShellScript "run-amadeus-cli" ''
              # Suppress output unless there's an error
              if ! cmake -B build -DBUILD_TESTS=OFF > /dev/null 2>&1; then
                echo "Build configuration failed"
                exit 1
              fi

              if ! cmake --build build > /dev/null 2>&1; then
                echo "Build failed"
                exit 1
              fi

              ./build/bin/amadeus-cli "$@"
            '');
          };

          # Test runner
          test = {
            type = "app";
            program = toString (pkgs.writeShellScript "run-tests" ''
              if [ ! -d "build" ]; then
                cmake -B build
              fi
              cmake --build build
              ctest --test-dir build --output-on-failure
            '');
          };

          # Format code
          format = {
            type = "app";
            program = toString (pkgs.writeShellScript "format-code" ''
              echo "Formatting all C++ code..."
              find src include test -name "*.cpp" -o -name "*.h" -o -name "*.hpp" | xargs ${pkgs.clang-tools}/bin/clang-format -i -style=file
              echo "Formatting complete."
            '');
          };

          # Check formatting
          format-check = {
            type = "app";
            program = toString (pkgs.writeShellScript "check-format" ''
              echo "Checking formatting of all C++ code..."
              find src include test -name "*.cpp" -o -name "*.h" -o -name "*.hpp" | xargs ${pkgs.clang-tools}/bin/clang-format -n -Werror -style=file
              if [ $? -eq 0 ]; then
                echo "All files formatted correctly."
                exit 0
              else
                echo "Some files need formatting. Run 'nix run .#format' to fix."
                exit 1
              fi
            '');
          };
        };
      }
    );
}
