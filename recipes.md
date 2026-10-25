# Recipes

Each recipe is small, complete, and
uses only machinery the earlier
chapters proved.

## Add a second board to an old project

*You have a working project for one
board; a different board should run
the same thinking.*

1. Add a section naming the new target.
   For a hypothetical second board:
   `[env:nano]` with `platform =
   atmelavr`, `board = nanoatmega328`,
   `framework = arduino`.
2. If the board's program differs (a
   different pin, no LED), write its
   front end as a new file in `src/`
   and give the new environment a
   `build_src_filter` for it. If the
   same program serves, point the new
   env's filter at the existing file.
3. Build the new env alone first:
   `pio run -e nano`. Expect downloads:
   a new board in a known platform may
   need nothing new; a new *platform*
   brings its toolchain with it.
4. When it builds, decide whether it
   joins `default_envs`. The library,
   its tests and the shared `[env]`
   settings required no edits — that
   is the pattern working as designed.

## Pin a library before it breaks you

*A project that built last spring
fails today, or builds differently.*

Look at its `lib_deps`. An entry with
no version, or a bare name installed
by hand long ago, resolves to
"latest" *at every fresh build* — the
project was never reproducible, only
lucky. Fix it the guide's way:
`pio pkg install -e ENV --library
OWNER/NAME` once, and let the tool
write the pinned line
(`@^7.4.3`-style) into the file. Commit
the file. A future you, on another
machine, now builds the same code —
and if you ever *want* the newer
library, upgrading becomes one edited
line and a test run, not an accident
discovered at the workbench.

## The clean rebuild

*The build behaves as if it is
remembering something you deleted.*

```bash
pio run -t clean     # per project; add -e for one env
rm -rf .pio          # the whole local build state
pio run
```

`.pio/` holds build products and the
project's downloaded libraries; all of
it is re-derived from `platformio.ini`
and your sources, so deleting it costs
one slower build and loses nothing.
The platform and toolchain store in
the core directory is *not* touched
by this — a clean project rebuild is
cheap precisely because the store
survives. Reach for it when a flag
"did nothing", a renamed file still
seems to compile, or a library change
is not reflected — before doubting
anything else.

## Check a project out on a second machine

*The true test of everything in this
guide.*

Copy the project folder **without**
its `.pio/` (version control does
this naturally — `.pio` is in the
generated `.gitignore`). On the new
machine, install Core (chapter 3),
then:

```bash
pio run
pio test -e native
```

The first command rebuilds every
default environment, fetching each
platform, package and pinned library
at the versions the file names. If the
two machines' summary tables agree,
the project — not the machine — is
the thing that works. That property,
bought entirely by one honest file,
is the reason PlatformIO exists.

## A release and a debug twin

*Same board, two temperaments.*

Duplicate the board's environment
with `extends`, which inherits an
existing environment wholesale, and
let the copy carry the flag the plain
one lacks:

```ini
[env:uno-debug]
extends = env:uno
build_flags = -DENABLE_LOGGING
```

The logging build keeps the chatty
code the `#ifdef` in chapter 10
allows; the plain build compiles
without it (the shared `[env]` flags
reach both, as chapter 5 describes).
Build both and compare the flash
lines: the difference is the true
price of your logging, printed by the
tool instead of guessed by you.
