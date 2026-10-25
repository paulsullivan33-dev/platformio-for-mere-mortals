# Your First Project

The guide's one project is created the
way yours will be: with `pio project init`.
It is a small thing on purpose — a
**running average**: feed it sensor-style
readings, and it reports the mean of the
most recent few. The same averages are
wanted in a desktop test harness and on
a board with a blinking LED, which is
exactly the shape that shows PlatformIO
off.

## Creating the project — and the first error

```bash
mkdir averager
pio project init --project-dir averager --board uno
```

The `mkdir` is not ceremony. In Core
6.2.0 the command refuses a directory
that does not exist yet:

```text
Error: Invalid value for '--project-dir' / '-d':
Directory 'averager' does not exist.
```

Create it first and the same command
succeeds — and, on a fresh machine,
keeps going: initialising for a board
resolves that board's platform, so the
first downloads happen right here. The
lab watched `atmelavr`, the AVR
toolchain, the Arduino AVR framework and
the SCons build tool arrive before the
project existed (transcript `t01`). Your
first initialisation is slow for the
same reason your first build will be
fast: the store is being filled.

What you get:

```text
averager/
├── include/        headers shared by the whole project
├── lib/            your private libraries live here
├── src/            the programs themselves
├── test/           unit tests
└── platformio.ini  the project file
```

and an initial `platformio.ini` naming
just the one environment you asked for,
`[env:uno]`.

## The desktop twin comes first

Before touching the board build, the
guide adds a second environment that
compiles the project for the machine
you are sitting at (the full anatomy of
the file is chapter 5; for now, accept
the lines):

```ini
[env:native]
platform = native
build_src_filter = +<native_main.cpp>
```

plus a first program, `src/native_main.cpp`,
which feeds the averager six fixed
readings and prints each running
average. The library it uses arrives in
chapter 7; if you are following along,
create it there and come back — the
build below is the one from the lab,
library and all.

```bash
pio run -e native
```

Check (transcript `t02`):

```text
Linking .pio/build/native/program
========================= [SUCCESS] =========================
```

and the program runs, here, now:

```bash
.pio/build/native/program
```

```text
reading 21.0 -> average of last 1: 21.00
reading 21.4 -> average of last 2: 21.20
reading 20.9 -> average of last 3: 21.10
reading 21.8 -> average of last 4: 21.27
...
```

Pause on why this matters. A program
for a board usually cannot be run at
all until the board, the lead and the
upload all cooperate. The `native`
environment removes that wall for
everything except the parts that
genuinely touch hardware: logic,
arithmetic, formatting, parsing — the
bulk of most firmware — can be compiled
and *run* on your desk in about a
second. The board build then becomes a
formality you perform at the end of a
working day, not the only way to find
out anything. Every later chapter leans
on this twin.

## Check: what just happened

One project folder; one file describing
two targets; the desktop target built
and ran. If your output's numbers match
the transcript's, your Core, your
compiler and the project shape are all
sound — and any future failure can be
blamed on something more specific.
