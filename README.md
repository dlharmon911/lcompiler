# lcompiler

`lcompiler` is a manifest compiler for Allegro-based applications. It reads an XML manifest and generates a matching C header and source file that bootstrap the application setup code for you.

Instead of hand-writing repetitive initialization code, you describe the app in XML and let the compiler emit the C glue needed to:

- install Allegro and requested addons
- install input devices
- configure the application window
- create the display, timer, and event queue
- expose helper functions for setup and teardown

## What it generates

Given a manifest, the compiler produces two C files using the selected output prefix:

- `<prefix>.h`
- `<prefix>.c`

The generated header contains constants and declarations derived from the manifest, and the generated source contains the implementation code that initializes and cleans up the runtime objects.

With the default prefix, the generated files are:

- `manifest.h`
- `manifest.c`

## What goes into the manifest

The XML manifest describes the parts of an Allegro application that should be generated. In this repository, the sample manifest in `test/manifest.xml` defines:

- Allegro addons such as image, font, audio, acodec, and primitives
- input devices such as keyboard and mouse
- application metadata such as the window title
- display settings such as width, height, flags, and display options
- timer configuration

From that input, the compiler generates code such as:

- manifest-level `#define` values like title, display size, and timer speed
- a `manifest_data_t` struct for core Allegro objects
- helper functions including:
  - `manifest_install_allegro()`
  - `manifest_uninstall_allegro()`
  - `manifest_zero_data()`
  - `manifest_initialize_data()`
  - `manifest_uninitialize_data()`

## Command line usage

The built-in help describes the command line interface as:

`Usage: lcompiler [options] <file>`

Options:

- `-h`, `--help` - Show the help message
- `-v`, `--version` - Show version information
- `-o`, `--output` - Specify the output name prefix used for generated files
- `-d`, `--directory` - Specify the output directory

For example, using the prefix `manifest` generates `manifest.h` and `manifest.c`.

## Example in this solution

The `test` project shows the intended workflow end to end:

- `test/manifest.xml` is the source manifest
- `test/manifest/manifest.h` and `test/manifest/manifest.c` are generated from that manifest
- `test/src/main.c` includes `manifest.h` and uses the generated functions to initialize, run, and shut down the application

In practice, the generated files act as a thin application bootstrap layer, leaving `main.c` free to focus on the app loop, input handling, update logic, and rendering.

## Summary

`lcompiler` turns a declarative XML manifest into reusable C source files for Allegro application startup. It is meant to reduce boilerplate, keep initialization consistent, and make it easier to spin up applications from a simple manifest description.
