{ pkgs }: {
	deps = [
   pkgs.nlohmann_json
		pkgs.clang
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}