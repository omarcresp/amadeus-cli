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

        commonInputs = with pkgs; [
          cmake
          ninja
          cli11
          gtest
        ];

        devInputs = with pkgs; [
          clang-tools
          ccls
          gdb
          valgrind
        ];

      in {
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "amadeus-cli";
          version = "0.0.1";
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

        apps.test = {
          type = "app";
          program = toString (pkgs.writeShellScript "run-tests" ''
            if [ ! -d "build" ]; then
              cmake -B build
            fi
            cmake --build build
            ctest --test-dir build --output-on-failure
          '');
        };
      }
    );
} 