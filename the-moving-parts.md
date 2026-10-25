# The Moving Parts

PlatformIO is a small command driving a
storehouse. Five parts do the work; when
something surprises you later, it is
almost always one of these five behaving
exactly as designed.

## Core — the command itself

**PlatformIO Core** is a Python program,
the `pio` command. It parses your
`platformio.ini`, works out what is
needed, fetches what is missing, and
drives the builds by calling a build
engine (SCons, which arrives as one of
the packages below). Core itself knows no
board and no chip; all of that knowledge
lives in the platforms. The lab installed
Core 6.2.0, and every transcript in the
guide is Core's own output.

## Platforms — the knowledge of a chip family

A **platform** is a downloadable bundle
describing one family of chips: which
compilers it needs, which boards exist,
how uploads work. The guide uses two:

- `atmelavr` (5.3.0 in the lab) — Atmel/Microchip
  AVR chips, the Arduino Uno among them.
- `native` (1.2.1) — no chip at all: build
  for the machine you are sitting at,
  with its own compiler.

You name a platform in the project file;
Core downloads it once and keeps it.

## Packages — the tools themselves

Platforms are recipes; **packages** are
the ingredients. Compilers
(`toolchain-atmelavr`, gcc 7.3.0 inside),
frameworks (`framework-arduino-avr`, the
Arduino core libraries for AVR), upload
tools (`tool-avrdude`), the test library
(Unity), the static checker (cppcheck) —
each is a package with a version, fetched
on first use. The lab's first Uno build
needed four of them; the store that holds
them all is measured in chapter 15,
because the number surprises everyone
the first time: this guide's downloads
came to about 300 MB.

## The registry and lib_deps — other people's code

The **PlatformIO Registry** is a public
library catalogue: thousands of libraries,
each with an owner, a name and versions.
Your project declares the ones it uses
under `lib_deps` in `platformio.ini`:

```ini
lib_deps = bblanchon/ArduinoJson@^7.4.3
```

`pio run` then fetches exactly those,
into the project's own `.pio/libdeps/`
folder — a per-project shelf, so two
projects can use different versions of
the same library without quarrelling.
Chapter 8 installs one for real.

## The LDF — the part that finds your libraries

The **Library Dependency Finder** reads
your source code's `#include` lines and
works out which libraries — registry ones
and the private ones in your project's
`lib/` folder — each environment needs,
then compiles exactly those. Its report
appears in every build:

```text
Dependency Graph
|-- ArduinoJson @ 7.4.3
|-- RunningAverage @ 1.0.0
```

When a build complains it cannot find a
header, it is the LDF you are arguing
with; chapter 16 teaches the argument.

## Where everything lives

| Part | Where it sits |
|---|---|
| Core | your Python environment (the lab used a venv) |
| Platforms and packages | the **core directory**, `~/.platformio` by default; the lab moved it with `PLATFORMIO_CORE_DIR` |
| A project's downloads | `<project>/.pio/` — builds and that project's libraries |
| Your code | `src/`, `lib/`, `include/`, `test/` in the project folder |

The `.pio` folder is the one to remember:
it is entirely rebuilt from the project
file and your sources, so it is safe to
delete — and chapter 14's clean-rebuild
recipe does exactly that.

## Check: name the part

A build fails because the compiler for
your new board is missing → a **package**
the **platform** asked for. A header is
not found → the **LDF**. A library version
changed under you → the **registry**
entry in `lib_deps`. Keep the five parts
apart and most error messages read as
sentences instead of weather.
