{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell rec {

  name = "iss";

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

