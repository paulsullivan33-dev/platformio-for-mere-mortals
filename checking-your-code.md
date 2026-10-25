# Checking Your Code

Compilers check that code is *legal*.
A **static checker** reads the same
code looking for things that are legal
and still wrong: variables used before
they are set, functions that can never
be called, arithmetic that can overflow
its type. PlatformIO wraps the checker
as `pio check`, and the lab ran it for
real.

```bash
pio check -e native
```

The first run downloads the checker
package (`tool-cppcheck`, transcript
`t07`), then reads your project and
reports. The guide's results, in full,
because interpreting them is the
chapter:

```text
src/arduino_main.cpp:17: [low:style] The function 'setup' is never used. [unusedFunction]
src/arduino_main.cpp:22: [low:style] The function 'loop' is never used. [unusedFunction]
.pio/libdeps/native/ArduinoJson/.../preprocessor.hpp:7: [high:error]
    failed to expand 'ARDUINOJSON_BEGIN_PUBLIC_NAMESPACE' ...
```

and a summary table: 1 high, 0 medium,
2 low — verdict **PASSED**, because by
default `pio check` reports at these
severities without failing the run.
(Thresholds are configurable per
environment with `check_tool` and
related options; a stricter project
can make findings fail the build.)

## Reading findings like an owner

Those three lines contain the whole
skill, because none of them is what it
first seems:

1. **`setup`/`loop` "never used"** —
   *true and harmless.* Nothing in the
   project calls them; the Arduino
   framework does, from outside the
   analysed code, on the board this
   environment never builds. The
   checker also scanned a file this
   environment excludes by source
   filter — checkers read folders, not
   intentions. Verdict: known, explained,
   ignored *on the record*.
2. **A high-severity error in
   ArduinoJson's headers** — *not your
   bug, and not ArduinoJson's either.*
   It is cppcheck's own preprocessor
   giving up on that library's macro
   machinery. Checkers analyse your
   dependencies with the same zeal as
   your code, and a fraction of what
   they report is the sound of the tool
   meeting code it cannot model.
   Verdict: identified as tool noise;
   the library itself builds and runs
   proven-correct in chapter 8's
   transcript.
3. **Your own library: silence.** No
   lines about `RunningAverage` — the
   most valuable output a checker
   gives, precisely because it is
   boring.

The discipline is the same one a good
compiler-warning habit teaches: every
finding gets *classified* — mine and
real, mine and harmless, not mine at
all — and the classification, not the
raw count, is what you act on. A
project that chases "zero findings"
by suppressing the checker wholesale
has traded a smoke alarm for a quiet
room.

## Where check fits

Between the build and the tests, in
cost order: `pio run` proves it
compiles, `pio check` reads it
suspiciously, `pio test` proves it
behaves. All three run on the desktop,
in seconds, before any board is
involved — which is, for the last
time in this guide, the desktop twin
paying for its keep.

## Check: run it before you need it

Adopt `pio check` on a project while
it is small and its findings are few
enough to classify one by one. The
first run on a large, old project is
a hundred lines of other people's
priorities; the first run on a young
one is a habit forming.
