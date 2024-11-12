{
  description = "Meson hello world example";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs =
    inputs@{
      self,
      nixpkgs,
      flake-parts,
    }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [ "x86_64-linux" ];

      perSystem =
        { pkgs, ... }:
        let
          stdenv' = pkgs.gcc14Stdenv;
        in
        {
          devShells.default =
            pkgs.mkShell.override
              {
                stdenv = stdenv';
              }
              rec {
                packages = with pkgs; [
                  nixd
                  nixfmt-rfc-style

                  meson
                  mesonlsp
                  ninja
                  pkg-config

                  qt6.full
                  qtcreator

                  # llvmPackages.clang-unwrapped
                  clang-tools
                ];

                CPATH =
                  "${stdenv'.cc.libc.dev}/include:"
                  + "${stdenv'.cc.cc}/lib/gcc/x86_64-unknown-linux-gnu/${stdenv'.cc.version}/include";
                C_INCLUDE_PATH = CPATH;
                CPLUS_INCLUDE_PATH =
                  "${stdenv'.cc.cc}/include/c++/${stdenv'.cc.version}:"
                  + "${stdenv'.cc.cc}/include/c++/${stdenv'.cc.version}/x86_64-unknown-linux-gnu:"
                  + CPATH;
              };
        };
    };
}
