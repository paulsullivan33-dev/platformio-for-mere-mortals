# What PlatformIO Is

PlatformIO builds programs for **boards**:
small computers on a circuit board — an
Arduino Uno, an ESP32 module, a
microcontroller on a sensor board — whose
entire job is to run one program, yours,
from the moment power arrives. Building
such a program on your own machine means
four jobs, and they are the four jobs
PlatformIO organises:

1. **Compiling with the right compiler.**
   Your computer's processor and the
   board's speak different machine code.
   The build needs a *cross-compiler* for
   the board's chip, plus the libraries
   that know the board (its **framework**).
2. **Managing libraries.** Board programs
   lean on libraries for sensors, screens
   and radios. Each must be found, fetched
   at a known version, and compiled too.
3. **Checking the fit.** A board's memory
   is tiny — the Uno in the lab has 32 KB
   of program space and 2 KB of RAM — so
   the build must report the size honestly.
4. **Uploading.** The finished program
   (the **firmware**) travels down a USB
   lead into the chip, a step called
   *flashing* or *uploading*.

PlatformIO's promise is that one command,
`pio run`, does jobs 1–3, and one more,
`pio run -t upload`, does job 4 — for any
of thousands of boards, because everything
that differs between boards is written
down in one file per project,
`platformio.ini`, instead of living in
your head or in an editor's settings.

## What PlatformIO is not

- **Not an editor.** PlatformIO Core, the
  subject of this guide, is a command-line
  tool. There is a popular extension that
  puts it inside the VS Code editor
  (PlatformIO IDE), which many people meet
  first — but the engine underneath is the
  same Core, and everything in this guide
  works in a plain terminal.
- **Not a compiler.** It owns no compiler
  at all. It *downloads* the correct
  toolchain for your board the first time
  a project needs it, keeps it in a store
  on disk, and drives it. Chapter 2 names
  the parts.
- **Not a board or a cloud account.** It
  runs entirely on your machine, offline
  once the downloads are done, and it
  needs no sign-in for anything this
  guide does.

## The shape of the idea

A PlatformIO **project** is a folder. In
it sit your source code, your private
libraries, your tests — and the one file
that describes the whole arrangement:

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
```

That stanza is an **environment**: "build
this project for an Arduino Uno, using
the AVR platform and the Arduino
framework." A project may carry several
environments — the guide's project has
two, one for a real Uno and one called
`native` that builds the same code for
your own desktop, where it can be run and
tested directly. That second environment
is the single most useful idea in this
guide, and chapter 9 is built around it.

Everything else follows from the file.
Change the board name and PlatformIO
fetches a different toolchain. Name a
library and it appears from the registry,
pinned to a version. Nothing about the
build lives in the editor, the phase of
the moon, or the machine you happen to
be sitting at — which is why a project
can be copied to another computer and
rebuilt exactly, a property chapter 14
puts to work.

## Check: the idea in one breath

If you can say "PlatformIO reads one file
that names the board, the libraries and
the settings, fetches whatever tools that
implies, and builds — the same way on any
machine," you have the model. The rest of
the guide is the detail, earned one real
build at a time.
