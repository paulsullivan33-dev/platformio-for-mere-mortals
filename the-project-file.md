# The Project File

Everything PlatformIO knows about your
project lives in one file at the project
root: `platformio.ini`. It is an INI
file — sections in `[brackets]`,
`key = value` lines, `;` comments — and
learning to read it is most of learning
PlatformIO. Here is the guide's project
file in full, as the lab left it:

```ini
[platformio]
default_envs = native, uno

[env]
build_flags = -DSAMPLE_COUNT=3

[env:native]
platform = native
build_src_filter = +<native_main.cpp>
lib_deps = bblanchon/ArduinoJson@^7.4.3

[env:uno]
platform = atmelavr
board = uno
framework = arduino
build_src_filter = +<arduino_main.cpp>
monitor_speed = 9600
```

## The sections

- **`[platformio]`** — housekeeping for
  the project as a whole. `default_envs`
  lists what a bare `pio run` builds;
  without it, `pio run` builds *every*
  environment, which is also fine and
  sometimes what you want.
- **`[env]`** — settings inherited by
  every environment. Options here are
  the project's defaults: a build flag,
  a library every target needs, a
  monitor speed. Chapter 10 uses it for
  the guide's one shared flag.
- **`[env:NAME]`** — one environment
  each. The three lines that matter
  most:
  - `platform` — the chip family bundle
    to build with (`atmelavr`, `native`).
  - `board` — the exact board (`uno`).
    Names come from PlatformIO's board
    catalogue; `pio boards` lists them.
  - `framework` — the library world the
    code is written against (`arduino`
    here). The `native` environment
    needs no board or framework lines:
    there is no board.
- **Per-environment options** — anything
  set in an `[env:NAME]` section
  overrides or extends the shared
  `[env]` for that target alone:
  `lib_deps` for libraries only this
  target uses, `build_src_filter` for
  which sources belong to it (chapter
  9), `monitor_speed` for the serial
  monitor (chapter 13).

## Options you will meet constantly

| Option | What it controls |
|---|---|
| `platform`, `board`, `framework` | what you are building for |
| `lib_deps` | registry libraries, pinned (chapter 8) |
| `build_flags` | flags handed to the compiler (chapter 10) |
| `build_src_filter` | which files in `src/` this env compiles (chapter 9) |
| `monitor_speed`, `monitor_port` | the serial monitor (chapter 13) |
| `upload_port`, `upload_speed` | uploading (chapter 13) |
| `test_framework` | how `pio test` builds tests (chapter 11) |

There are hundreds more in the official
project-configuration reference; the
honest way to meet them is one at a
time, when a build needs one.

## The file edits itself — a behaviour to know

PlatformIO treats `platformio.ini` as
*its* file as much as yours. When the
lab ran `pio pkg install --library
bblanchon/ArduinoJson`, the tool wrote
the `lib_deps` line into `[env:native]`
itself — convenient and correct. Less
convenient, observed in the same edit:
comments the author had placed beside
the sections the tool rewrote did not
survive the rewrite. The header banner
did; the section notes did not.

So: keep explanations in your README or
in comments at the top of the file, let
the tool own the sections it manages,
and keep the project under version
control so any rewrite is one `diff`
away from being understood. None of
this is a defect to rage against — a
tool that manages dependencies *in* the
file must be able to write the file —
but the first silent rewrite surprises
everyone, and now it will not surprise
you.

## Check: read a stranger's file

Handed any PlatformIO project, open
this file and answer three questions:
which environments exist, what board
and libraries each implies, and what a
bare `pio run` will do. That is the
whole first impression, and it is
always available — no editor, no
account, no board required.
