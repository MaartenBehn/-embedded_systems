{ pkgs ? import <nixpkgs> {} }:

let
  riscv32-pkgs = import <nixpkgs> {
    crossSystem = (import <nixpkgs/lib>).systems.examples.riscv32-embedded;
  };

  riscv64-pkgs = import <nixpkgs> {
    crossSystem = (import <nixpkgs/lib>).systems.examples.riscv64;
  };

in
riscv32-pkgs.mkShell rec {

  name = "embedded_systems";

  nativeBuildInputs = [
      # Uncomment to also bring QEMU, if you don't have it system-wide.
      # riscv64-pkgs.buildPackages.buildPackages.qemu
      riscv32-pkgs.buildPackages.gdb
    ];
 

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

  shellHook = '' 
    export PATH="/home/stroby/dev/embedded_systems/ueb02/riscv-gnu-toolchain/install/bin:$PATH"
  '';
}

