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
          cli11
          gtest
        ];

        # Development shell additional inputs
        devInputs = with pkgs; [
          clang-tools
          ccls
          gdb
          valgrind
          git
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
            echo "Available commands:"
            echo "  cmake -B build      # Configure the project"
            echo "  cmake --build build # Build the project"
            echo "  ctest --test-dir build # Run tests"
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
        };
      }
    );
} 