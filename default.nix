with import <nixpkgs> {}; {
  test = clangStdenv.mkDerivation rec {
    name = "logger";
    buildInputs = [
      cmake
      ninja
    ];
    src = ./.;
    buildPhase = ''
      mkdir -p $out/tmp
      cd $out/tmp/
      cmake $src -GNinja
      ninja
    '';
    installPhase = ''
      mkdir -p $out/bin $out/include
      cp $out/tmp/example $out/bin/
      cp $src/logger.h $out/include/
    '';
  };
}
