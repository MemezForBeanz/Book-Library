{ pkgs }: {
    deps = [
        pkgs.nlohmann_json
        pkgs.clang
        pkgs.ccls
        pkgs.gdb
        pkgs.gnumake
        pkgs.python3  # Add Python
        pkgs.python3Packages.flask # Add Flask
    ];
}