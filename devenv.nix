{ pkgs, ... }:

{
  packages = [
    pkgs.SDL
    pkgs.gcc
  ];

  languages.c.enable = true;

  enterShell = ''
    which gcc
    gcc --version
    echo "LFG!"
  '';
}
