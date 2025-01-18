{ pkgs ? import <nixpkgs> {} }:

let
  riscv32-pkgs = import <nixpkgs> {
    crossSystem = (import <nixpkgs/lib>).systems.examples.riscv32-embedded;
  };

  riscv64-pkgs = import <nixpkgs> {
    crossSystem = (import <nixpkgs/lib>).systems.examples.riscv64;
  };

in
pkgs.mkShell rec {

  name = "riscv32";

  packages = with pkgs; [
    digital
    cmake 
    gnumake
    boost
    libarchive
    bison
    flex
    gnum4
  ];
}

