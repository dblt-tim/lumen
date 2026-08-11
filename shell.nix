{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    pkgsCross.x86_64-embedded.buildPackages.gcc
    pkgsCross.x86_64-embedded.buildPackages.binutils

    xorriso
  ];
}