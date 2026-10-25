# Many Environments

An **environment** is one complete
answer to the question "build this
project for what, how?" The guide's
project has two, and they share almost
everything — sources, the library, one
build flag — while differing in the
three ways that matter: the toolchain,
the front-end program, and one library.
That shape, *one project, several
targets*, is PlatformIO's home ground,
and it generalises: the same pattern
holds a debug and a release build, two
boards on one product, or a simulator
beside the hardware.

## What is shared, what is not

| | shared | per-environment |
|---|---|---|
| sources | `lib/`, `include/` | the `src/` files each env selects |
| settings | anything in `[env]` | anything in `[env:NAME]` wins |
| downloads | the core directory's platforms | `.pio/build/<env>/`, `.pio/libdeps/<env>/` |

The mechanism is section inheritance:
an option set in `[env]` applies
everywhere; the same option in
`[env:uno]` overrides it for the Uno
alone. Nothing cleverer is happening,
which is why it can be reasoned about.

## The source filter: two programs, one src/

The one real puzzle in a multi-target
project is `src/`. A desktop program
starts at `main()`; an Arduino program
starts at `setup()` and `loop()`. Both
files cannot be compiled into both
firmwares. The guide's split:

- `src/native_main.cpp` — the desktop
  twin: `main()`, terminal output.
- `src/arduino_main.cpp` — the board
  program: `setup()`/`loop()`, LED and
  serial output.

and each environment claims its own
with **`build_src_filter`**:

```ini
[env:native]
build_src_filter = +<native_main.cpp>

[env:uno]
build_src_filter = +<arduino_main.cpp>
```

A filter of `+<file>` means "of `src/`,
compile this". (The default, when no
filter is set, is everything — which is
why single-board projects never meet
this option, and why the first
two-program project fails to link with
duplicate `main`-style errors until it
does.) Anything both programs need does
not belong in either file; it belongs
in `lib/`, which both environments
compile unfiltered — the arrangement
chapter 7 argued for, here paying its
rent.

## Choosing what builds

```bash
pio run              # default_envs: both
pio run -e uno       # just this one
pio run -e native    # just the twin
```

The summary table at the end of a full
run is the scoreboard (`t05`):

```text
Environment    Status    Duration
-------------  --------  ------------
native         SUCCESS   00:00:02.799
uno            SUCCESS   00:00:04.921
```

Two practical notes. Builds are
independent: a broken Uno environment
does not stop the native one from
building, testing and passing, which is
how a hardware problem stays a hardware
problem instead of becoming a whole
project's problem. And build time adds
up per environment — the desktop twin
is the cheap one you run a hundred
times a day; the board builds are the
ones you run when the twin is happy.

## Growing to three

Adding a target later is the same
shape again: a new `[env:...]` section,
its board and platform named, its
source filter pointed at a new
front-end file if the hardware differs,
and `default_envs` updated if it should
join the default build. The library,
the tests and the shared settings do
not move. Chapter 14's first recipe
walks the steps.

## Check: the pattern in one line

If your project can say "same thinking
in `lib/`, thin front ends in `src/`,
one environment per target," it can
grow a new board, a simulator or a
test harness without restructuring —
the file changes, the code does not.
