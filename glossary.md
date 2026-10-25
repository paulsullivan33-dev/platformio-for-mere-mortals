# Glossary

**Board** — a circuit board carrying a
microcontroller, ready to program: an
Arduino Uno, an ESP32 development
board. The target of everything in
this guide.

**Core** — PlatformIO Core, the `pio`
command-line program itself. It owns
no compiler; it organises the parts
that do the work.

**Core directory** — the store where
platforms and packages live:
`~/.platformio` by default, movable
with `PLATFORMIO_CORE_DIR`.

**Cross-compiler** — a compiler that
runs on one kind of processor and
produces machine code for another:
gcc on your laptop emitting AVR code
for an Uno.

**Environment (env)** — one complete
build configuration in
`platformio.ini`: an `[env:NAME]`
section naming platform, board,
framework, libraries and flags.

**Firmware** — the program as the
board holds it: the compiled binary
(`firmware.hex`, `firmware.elf`)
destined for the chip's flash memory.

**Flash (memory)** — the board's
non-volatile program storage; keeps
the firmware with power off. Also,
as a verb, the act of uploading.

**Framework** — the library world a
program is written against: `arduino`
in this guide; others include ESP-IDF
and Zephyr.

**LDF (Library Dependency Finder)** —
the part of PlatformIO that reads
your `#include`s and decides which
libraries each environment compiles.

**Library** — reusable code with a
name and (ideally) a version: yours,
in `lib/`, or the registry's, via
`lib_deps`.

**library.json** — a library's
manifest: name, version, description,
and which platforms and frameworks it
serves.

**lib_deps** — the `platformio.ini`
option listing a project's registry
libraries, with their version pins.

**Native** — the platform that builds
for the machine you are sitting at,
with its own compiler. The desktop
twin's home.

**Package** — a downloadable tool
bundle: a toolchain, a framework, an
upload tool, a checker.

**Pin** — a version constraint in
`lib_deps` (`@^7.4.3`) that keeps a
library's version from drifting
between builds.

**Platform** — a downloadable bundle
describing one chip family: its
boards, packages and upload methods
(`atmelavr`, `native`).

**RAM** — the board's working memory:
variables, buffers, stack. On an Uno,
2 KB of it; the size report's second
line.

**Registry** — the PlatformIO
Registry, the public catalogue of
libraries that `pio pkg` searches and
installs.

**Serial monitor** — the tool that
shows what a board prints over its
USB serial line, and the window into
a running program's mind:
`pio device monitor`.

**Source filter (`build_src_filter`)**
— the option deciding which files in
`src/` an environment compiles; the
multi-target project's traffic cop.

**Toolchain** — the compiler and its
companions (linker, archiver) for one
chip family, delivered as a package.

**Unity** — the small C unit-test
framework PlatformIO's `pio test`
uses by default.

**Upload** — sending firmware to the
board: `pio run -t upload`, via the
platform's tool (avrdude, for AVR),
down the USB lead, into flash.
