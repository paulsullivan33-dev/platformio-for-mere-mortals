# PlatformIO for Mere Mortals

A program for a small board — an Arduino,
an ESP32, a sensor node on a shelf — is
built differently from a program for a
computer. The compiler is not the one
your machine uses for itself: it is a
**cross-compiler** that speaks the board's
dialect of machine code. The libraries
come from somewhere, the board's memory
is measured in kilobytes, and at the end
somebody has to push the finished program
down a USB lead into the chip. **PlatformIO**
is the open-source tool that organises all
of that behind one command, `pio`: one
configuration file per project naming the
board, the libraries and the settings, and
PlatformIO fetches the right compiler,
builds the program, checks its size,
runs its tests, and uploads it. This guide
explains how that works in those terms —
and works one small project all the way
through, on the desktop and for a real
board.

The lab behind this guide ran the real
thing: **PlatformIO Core 6.2.0**, installed
with pip into a Python virtual environment
on a small Linux machine. One fixture
project — a running-average library with
two front ends — was created with
`pio project init`, built for the desktop
with the machine's own compiler and run
on the spot, built again for an **Arduino
Uno** with the genuine AVR toolchain
PlatformIO downloaded for the purpose
(the build ends in a real `firmware.hex`
and a memory report: 15% of the Uno's
flash, 13% of its RAM), extended with a
library fetched from the PlatformIO
registry and used in the code, rebuilt
with a changed build flag whose effect
is visible in the program's own output,
tested with four unit tests that all
pass, and scanned by the static checker
that `pio check` drives. The sizes are
printed by the tool, not estimated by
the author.

What the lab could not do, it did not
fake. The lab machine has **no board
attached** — no Arduino on a USB lead —
so the two steps that physically need
one, uploading the firmware and watching
the board over a serial monitor, are
taught from the documentation and from
the real errors the commands produce
when there is nothing to talk to (the
guide keeps those transcripts: an empty
device list, and an upload that stops
and explains itself). Likewise the
PlatformIO IDE — the popular editor
extension — and boards other than the
Uno are pointed at, not exercised.
`criteria.md` keeps the full ledger of
what was run and what was only read.

## What this guide covers

- [**What PlatformIO is**](what-platformio-is.md) —
  the mental model: one project file,
  fetched toolchains, and what PlatformIO
  is not (an editor, a compiler, a board)
- [**The moving parts**](the-moving-parts.md) —
  Core, platforms, packages, the library
  registry and dependency finder, and
  where each one keeps its files
- [**Installing PlatformIO**](installing-platformio.md) —
  the pip install into a virtual
  environment, the other install routes,
  and the core directory where downloads
  live
- [**Your first project**](your-first-project.md) —
  `pio project init`, the shape of a
  project, and a first build that runs
  on the desktop in front of you
- [**The project file**](the-project-file.md) —
  `platformio.ini` read properly:
  sections, environments, where options
  go, and the file's habit of being
  edited by the tool itself
- [**Building for a board**](building-for-a-board.md) —
  the Uno build end to end: the cross
  compiler, the framework, the size
  report, and the `.hex` file that comes
  out
- [**Your own libraries**](your-own-libraries.md) —
  code in `lib/`, the `library.json`
  manifest, and how the same library
  serves two programs at once
- [**Libraries from the registry**](libraries-from-the-registry.md) —
  finding, installing and pinning
  somebody else's library, and actually
  calling it in your code
- [**Many environments**](many-environments.md) —
  one project, several targets: shared
  settings, source filters, and choosing
  what builds — the desktop twin pattern
- [**Build flags**](build-flags.md) —
  settings that reach into the code as
  preprocessor defines, proven by
  changing one number and watching the
  output move
- [**Testing on the desktop**](testing-on-the-desktop.md) —
  unit tests with Unity, run by
  `pio test` against the native build —
  no board involved, none needed
- [**Checking your code**](checking-your-code.md) —
  `pio check` and cppcheck: what a static
  checker finds, and how to tell its
  real findings from noise in other
  people's headers
- [**Uploading and the monitor**](uploading-and-the-monitor.md) —
  the two steps that need the board in
  your hand: flashing firmware, serial
  output, ports and speeds — labelled
  documented-only, with the lab's real
  no-board errors shown
- [**Recipes**](recipes.md) — a new board
  added to an old project, a library
  pinned before it breaks you, a clean
  rebuild, and checking a project out on
  a second machine
- [**The neighbours**](the-neighbours.md) —
  the Arduino IDE and CLI, ESP-IDF,
  Zephyr, plain Make and CMake, and
  MicroPython: what each trades away
- [**Limits**](limits.md) — downloads
  measured in hundreds of megabytes, a
  registry you trust because you must,
  and the last metre to the board that
  no tool can walk for you
- [**Troubleshooting**](troubleshooting.md) —
  the directory that must exist first,
  the flag that changed nothing, the
  checker complaining about a library,
  and the upload with nowhere to go
- [**Glossary**](glossary.md) — the terms,
  collected in one place

## What it doesn't cover

Designing circuits, choosing a board for
a job, or the electronics on either side
of the pins — the guide starts where the
board already exists and a program needs
writing. Writing firmware itself, beyond
the small fixture project, is a subject
of its own (the Arduino and C++ guides
are the shelf-mates). Debugging a running
board with a hardware probe, the paid
PlatformIO Plus services, and building
products for manufacture are likewise
pointed at, not taught.

## How to use this guide

Read chapter 1 for the model and chapter
2 before installing anything — knowing
which part downloads what turns later
surprises into named events. Chapters 3
and 4 get you a project that builds and
runs on your own desktop in one sitting;
that desktop twin is the pattern the
whole guide leans on, because a build
you can run beats a build you can only
stare at. Chapter 5 is worth reading
before the file confuses you — it will,
once. Chapters 11 and 12 (tests and
checks) are the ones to adopt early,
while the project is small enough that
good habits cost minutes. The lab's
transcripts live in
`platformio-lab/transcripts/`; the whole
fixture project sits beside them in
`platformio-lab/averager/`, ready to
copy and build yourself.

---

## Part of the series

This guide is one of the [For Mere Mortals](https://paulsullivan33-dev.github.io/mere-mortals/) guides: plain-language guides to the tools programmers and makers use.

Related guides:

- [Arduino for Mere Mortals](https://paulsullivan33-dev.github.io/arduino-for-mere-mortals/)
- [MicroPython for Mere Mortals](https://paulsullivan33-dev.github.io/micropython-for-mere-mortals/)
- [ESPHome for Mere Mortals](https://paulsullivan33-dev.github.io/esphome-for-mere-mortals/)

## License

The writing in this guide is licensed under [CC BY 4.0](https://github.com/paulsullivan33-dev/platformio-for-mere-mortals/blob/main/LICENSE). Code examples and lab scripts are licensed under the [MIT License](https://github.com/paulsullivan33-dev/platformio-for-mere-mortals/blob/main/LICENSE-CODE).
