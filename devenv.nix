{ pkgs, ... }:

{
  packages = [ pkgs.SDL ];

  languages.c.enable = true;

  enterShell = ''
    gcc --version
  '';
}
