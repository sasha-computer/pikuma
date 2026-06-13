{ pkgs, ... }:

{
  packages = [
    pkgs.SDL2
    pkgs.gcc
  ];

  languages.c.enable = true;

  enterShell = ''
    # Regenerate clangd's flags with the current SDL2 store paths so the
    # editor LSP resolves <SDL2/SDL.h>. Self-heals after every devenv rebuild.
    printf '%s\n' -std=c99 $(pkg-config --cflags sdl2) > compile_flags.txt
    echo "LFG!"
  '';
}
