# Troubleshooting

Symptom → cause → fix, in the order
the lab (or every new user) meets
them.

**`Directory '...' does not exist`**
on `pio project init`.
The command will not create the
project directory for you in Core
6.2.0. `mkdir` it first, then init —
the lab's very first transcript
(`t01`) is this error and its fix.

**The build compiles the wrong
program, or links with duplicate
symbols.**
Two files in `src/` both define entry
points, and no `build_src_filter` is
telling the environments apart. Each
env must claim its front end
(chapter 9); shared code belongs in
`lib/`, which needs no filter.

**`fatal error: Something.h: No such
file or directory`.**
The Library Dependency Finder did
not connect that header to a library
it may use. Causes, in order: the
library is not declared in *this*
environment's `lib_deps` (registry
code), or not present under `lib/`
(private code), or declared but its
own `library.json` excludes this
platform or framework. `pio pkg list`
shows what the env actually resolved;
chapter 2 explains the machine you
are arguing with.

**I changed a build flag and nothing
changed.**
You edited a different environment's
section than the one you built; the
code never reads the define; or the
build state is stale. Chapter 10's
order: check the env, check the
`#ifndef`/`#ifdef` in the code, then
one clean rebuild (chapter 14)
before doubting further. And make
the program *print* the value — the
argument ends there.

**The checker reports a frightening
error in a library's header.**
Probably the checker's own
preprocessor meeting macro machinery
it cannot expand — the lab's
ArduinoJson finding (chapter 12) is
the type specimen. Classify before
you panic: whose file, whose fault,
does the code build and pass its
tests? Findings in *your* files are
yours; findings in dependencies are
information.

**`pio check` says `setup`/`loop`
are never used.**
They are called by the framework,
from outside the analysed project —
and the checker may also be reading
files a source filter excludes from
the build. Known, explained, ignorable
*once you can say why* (chapter 12).

**Upload: "Please specify
`upload_port`."**
No board was found. Work the chapter
13 list: lead plugged in at both
ends, `pio device list` — empty means
the *machine* cannot see the board
(cable, driver, on Linux the udev
rules) and no PlatformIO setting will
fix that; non-empty means name the
port in `upload_port` and retry.

**The monitor shows garbage
characters.**
The two baud rates disagree: the
program's `Serial.begin(...)` and
the environment's `monitor_speed`
must match. It is the serial
equivalent of listening on the wrong
station, and it has never once been
anything more sinister.

**The first build takes forever; the
second is instant.**
Not a fault: the first build fetched
a platform and its packages (watch
the download lines), the second found
the store full. Deleting `~/.platformio`
(or your `PLATFORMIO_CORE_DIR`) is how
you volunteer to pay the first-build
price again.

**A build that worked yesterday
fails today, untouched.**
Suspect anything unpinned: a
`lib_deps` without a version, a
platform left to float. `pio pkg list`
against yesterday's transcript — or
your version history — shows which
line moved. Chapter 14's pinning
recipe is the permanent fix.
