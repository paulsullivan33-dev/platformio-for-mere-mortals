# Libraries from the Registry

Your own `lib/` is for code only you
need. For everything the world has
already written — JSON parsers, sensor
drivers, screen libraries — there is
the **PlatformIO Registry**: a public
catalogue of libraries with owners,
versions and documentation, fetched by
name.

## Installing one, for real

The guide's desktop program ends by
printing its summary as JSON — work
nobody should hand-write when a good
parser exists. The lab installed the
best-known one (transcript `t03`):

```bash
pio pkg install -e native --library "bblanchon/ArduinoJson"
```

```text
Library Manager: ArduinoJson@7.4.3 has been installed!
```

Three things happened, each worth
seeing. The library was downloaded into
this project's own `.pio/libdeps/native/`
— not a global pile. The project file
gained a line, written by the tool:

```ini
lib_deps = bblanchon/ArduinoJson@^7.4.3
```

And the *pin* in that line is the real
lesson. `^7.4.3` means "7.4.3 or a later
7.x": close enough to receive fixes,
far enough to never wake up to a
version 8 that changed the rules. A
project file with pins, rebuilt on
another machine, fetches the same code
every time. A project file without
them rebuilds with whatever "latest"
means that week — chapter 15 counts
that as a limit, because it is one.

You can also write the `lib_deps` line
yourself and let the next `pio run`
fetch it; `pio pkg install` simply
does both steps at once and records
the version it actually got.

## Using it is just an include

With the dependency declared, the
desktop program gained six lines:

```cpp
#include <ArduinoJson.h>
...
JsonDocument doc;
doc["samples"] = samples;
doc["window"] = SAMPLE_COUNT;
doc["average"] = avg.average();
char line[128];
serializeJson(doc, line, sizeof(line));
```

and the rebuild's Dependency Graph
shows the new arrival before any code
compiles (`t03`): `ArduinoJson @ 7.4.3`
beside the private `RunningAverage`.
The program's last line — shown as
the final build prints it — is now:

```text
{"samples":6,"window":3,"average":21.86666667}
```

(The window reads 3 because chapter
10's experiment later changed it from
4; the line as first produced, window
4 and all, is in transcript `t03`.)

## Scoping: why the Uno never saw it

The install was aimed with `-e native`,
so the `lib_deps` landed in
`[env:native]` alone. The Uno build's
graph (`t04`, `t05`) contains no
ArduinoJson — its code would not have
fit the story anyway (the board
program prints plain text), and on a
2 KB-RAM chip, a library you do not
ship is memory you still have. Rule of
thumb: declare libraries in the
environment that uses them; promote
one to the shared `[env]` section only
when every target truly needs it.

## Finding and judging libraries

`pio pkg search <words>` searches the
registry from the terminal, and
`pio pkg show OWNER/NAME` prints an
entry's versions and requirements.
Judging what you find is a human task
with three quick checks: is it
**maintained** (a release in living
memory), does it **declare the
platforms and frameworks** you are
building for (its own `library.json`
says so, and the LDF will enforce it),
and do you need its **whole weight** —
on a desktop a library costs disk; on
a Uno it costs the flash and RAM lines
of chapter 6. The registry is a
commons, with a commons' mixture of
the excellent and the abandoned;
the pin in your project file is what
makes your choice reproducible either
way.

## Check: what is installed, exactly

```bash
pio pkg list
```

prints, per environment, the platform,
packages and libraries the project
currently resolves to — the definitive
answer to "what will this build
actually use," and the first thing to
paste into any request for help.
