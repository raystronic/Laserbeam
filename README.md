# Lazerbeam

Lazerbeam is a modular C program that dynamically loads and executes shared object (`.so`) files from an `ammo/` directory to perform actions on a specified target file. It features animated console output for visual feedback and is intended for controlled, experimental use.

![Alt text](https://i.pinimg.com/736x/7a/ac/16/7aac16f65b88573b63a5f1e2cf0e0043.jpg)

## Features
- Loads and executes missile plugins (`.so` files) from the `ammo/` directory.
- Displays animated ASCII art and text effects during execution.
- Supports listing available missile plugins and provides a help menu.
- Ensures safe execution in a controlled environment.

## Usage
```bash
./lazerbeam <missile.so> <target>  # Launch a missile at the target file
./lazerbeam -h                     # Display help and available missiles
./lazerbeam --list-ammo            # List available missile plugins
```

## How It Works
1. **Input Validation**: Checks for correct arguments (`<missile.so> <target>`), or displays help (`-h`) or missile list (`--list-ammo`).
2. **Dynamic Loading**: Loads the specified `.so` file from `ammo/` using `dlopen`.
3. **Animation**: Displays ASCII art from `art/art.art` and animated text effects using `animate_wave`.
4. **Execution**: Calls the `run` function from the loaded missile plugin, passing the target file as an argument.
5. **Cleanup**: Closes the dynamic library and exits.

## Requirements
- C compiler (e.g., `gcc`)
- POSIX-compliant system with `dlfcn.h` for dynamic loading
- `ammo/` directory containing `.so` missile plugins
- `art/art.art` file for ASCII art (optional)

## Compilation
```
make
make clean
```

## Notes
- Always test in a controlled environment to avoid unintended consequences.
- Ensure missile plugins are trusted, as they are dynamically executed.
- The program assumes `ammo/` and `art/` directories exist in the working directory.
