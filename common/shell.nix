with import <nixpkgs> {}; {
	myenv = stdenvNoCC.mkDerivation {
		name = "matlab";
		shellHook = "export PATH=\"/home/peter/apps/MATLAB/R2019b/bin:$PATH\"";
		buildInputs = [
			gcc7
			pkgconfig
			clp
			gsl
		];
	};
}
