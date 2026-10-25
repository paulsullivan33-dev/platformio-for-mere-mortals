# Build Flags

Some settings belong in the file, not
the code: how many readings the average
keeps, whether logging is chatty, which
hardware revision this firmware is for.
**Build flags** are how the project file
hands such values to the compiler. The
guide proves the mechanism with an
experiment, because a flag that changed
nothing is a flag you only think you
set.

## The setup: a default and an override

The shared header, `include/settings.h`,
carries the code's own default:

```cpp
#ifndef SAMPLE_COUNT
#define SAMPLE_COUNT 4
#endif
```

The `#ifndef` is the whole contract: if
nobody defines `SAMPLE_COUNT` from
outside, the code uses 4. The project
file then defines it from outside, in
the section every environment inherits:

```ini
[env]
build_flags = -DSAMPLE_COUNT=3
```

`-DNAME=value` is the compiler's own
spelling for "pretend this `#define`
came first," so the header's guard
steps aside and **3** is what both
programs are built with.

## The experiment

With the flag at 3, the lab rebuilt
everything and re-ran the desktop twin
(transcript `t05`). The output moved,
twice over:

```text
reading 21.8 -> average of last 3: 21.37
...
{"samples":6,"window":3,"average":21.86666667}
```

The average is over three readings,
not the header's four, because the
flag reached the code — and the Uno
build proved it too, silently: its
flash line changed between the two
builds (4,864 bytes in `t04`, 4,848 in
`t05`) because the smaller ring buffer
is smaller firmware. One line in
`[env]`, every target changed. A flag
set in `[env:uno]` instead would have
changed the board build alone; that
scoping choice — shared truth in
`[env]`, target truth in `[env:NAME]`
— is most of build-flag craft.

## What flags are for (and not for)

Good residents of `build_flags`:

- **Numbers the code parameterises** —
  window sizes, buffer lengths, timeouts,
  pin choices expressed as constants.
- **Feature switches** — `-DENABLE_LOGGING`
  tested with `#ifdef`, so the release
  firmware can leave the weight out.
- **Version and identity stamps** —
  a build date or revision the program
  can print about itself.

Poor residents: anything a *user* of
the finished device should be able to
change without recompiling (that's
runtime configuration, a different
chapter of a different book), and
anything secret — a flag is printed in
build output and lives in your version
history, so a password in `build_flags`
is a password published twice.

## When a flag "does nothing"

Three usual causes, in the order the
lab would check them. The environment
you built is not the one you edited
(flags in `[env:uno]` do nothing for
`-e native`). The code never tests the
name — a `#define` nobody reads is a
note to nobody. Or the build did not
rerun: PlatformIO tracks flag changes
and rebuilds what they touch, but a
suspicious result is always worth one
`pio run -t clean` before an hour of
doubt (chapter 14 gives the recipe).

## Check: the output is the evidence

Never settle a flag question by reading
files. Change the value, rebuild, and
make the *program* tell you which
value it was built with — a printed
line, a JSON field, a size that moved.
The guide's fixture prints its window
for exactly this reason; steal the
habit for your own first flag.
