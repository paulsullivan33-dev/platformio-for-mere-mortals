# Writing Criteria

Every guide in this repo is written to the same
standard. If you're adding or editing a guide —
human or AI — hold it to these.

1. **Plain words, real ideas.** Simple language,
   never dumbed-down concepts. Explain jargon on
   first use; collect terms in the glossary.
2. **No hype.** No marketing adjectives, no
   "revolutionary," no promises about what
   something will do for the reader.
3. **Honest about limits.** Say what the thing
   *can't* do. State uncertainty instead of
   smoothing it over. Validation notes include
   what remains unverified.
4. **No invented numbers.** Benchmarks, defaults,
   and specs are either measured or qualified with
   "depends on your setup." If it wasn't tested,
   say so.
5. **Checkable.** Commands are meant to be run,
   with "Check:" blocks showing what success looks
   like. Sources are linked, not asserted.
6. **Respect the reader's setup.** Call out
   Windows/Mac/Linux differences. Don't assume a
   GPU, a budget, or prior experience.
7. **Safety isn't skipped.** Real risks get
   stated plainly, not buried.
8. **Scoped.** Each guide says what it covers and
   points elsewhere for the rest. No guide
   pretends to be the whole subject.
9. **Structure over prose.** Tables, before/after
   examples, symptom → fix. Scannable beats essay.

## Verification notes for this guide

Built and verified 2026-10-24 against
**PlatformIO Core 6.2.0**, installed
with pip into a Python 3.12.3 virtual
environment on a 2-CPU, 7.7 GB sandbox
machine running Ubuntu 24.04, with the
core directory held in the workspace
(`PLATFORMIO_CORE_DIR`) so every
download could be measured: 304 MB
all told, itemised in
`examples/lab-notes.txt`.

**Primary sources read, not remembered:**
PlatformIO's official documentation
for the project configuration file
(section semantics, `build_src_filter`,
`default_envs`, `extends`), the
command reference (`pio run`, `pio
pkg`, `pio test`, `pio check`, `pio
device`), the library registry and
`library.json` manifest format, and
the udev-rules note for Linux uploads.

**The one limit, declared.** The lab
machine has no development board
attached and no way to attach one.
Everything up to the USB lead was run
for real; everything past it —
uploading to a board, the serial
monitor in use, `pio test` on
hardware — is documented only, and
chapter 13 is labelled as such on its
face. The no-board state itself was
recorded rather than worked around:
an empty `pio device list` and the
upload's `upload_port` error are kept
as transcript t08 and used as the
chapter's evidence.

**Ran for real** (transcripts in
`platformio-lab/transcripts/`; the
complete fixture project is in
`platformio-lab/averager/`):

- t00 — `pip install platformio` into
  a fresh venv; `pio --version` →
  PlatformIO Core 6.2.0.
- t01 — `pio project init --board
  uno`: first the genuine refusal
  ("Directory 'averager' does not
  exist"), then success after
  `mkdir`, with the atmelavr platform
  5.3.0, toolchain-atmelavr (gcc
  7.3.0) and framework-arduino-avr
  5.4.0 downloaded during init.
- t02 — `pio run -e native`: the
  native platform 1.2.1 installed,
  Unity 2.6.1 fetched, the shared
  library compiled and archived, the
  program **linked and run** — output
  quoted in chapter 4.
- t03 — `pio pkg list`, then `pio pkg
  install -e native --library
  bblanchon/ArduinoJson` →
  ArduinoJson 7.4.3 installed into the
  project and the pinned line
  `lib_deps = bblanchon/ArduinoJson@^7.4.3`
  written into `platformio.ini` by
  the tool; the desktop program
  changed to use it, rebuilt, and its
  JSON line printed for real.
- t04 — `pio run -e uno`: the full
  AVR framework compiled, firmware
  linked — RAM 268/2048 bytes
  (13.1%), Flash 4864/32256 bytes
  (15.1%) — and `firmware.hex`
  produced on disk.
- t05 — the shared build flag changed
  from its initial value 4 (which
  merely repeated the header's own
  default, proving nothing) to 3,
  and *both* environments rebuilt by
  a bare `pio run`: the desktop
  program's own output proves the new
  window (`"window":3`, averages over
  three readings), and the Uno flash
  figure moved to 4848 bytes.
- t06 — `pio test -e native`: four
  Unity unit tests of the shared
  library built and run on the
  desktop — 4 passed.
- t07 — `pio check -e native`:
  tool-cppcheck downloaded and run;
  the real findings (two low/style
  notes about `setup`/`loop`, one
  high/error inside ArduinoJson's
  own headers — cppcheck's
  preprocessor limit, not a defect
  in the library or the fixture) are
  classified in chapter 12.
- t08 — `pio device list` (empty)
  and `pio run -e uno -t upload`:
  tool-avrdude fetched, firmware
  rebuilt, upload stops at "Please
  specify `upload_port`…" — the
  honest no-board evidence behind
  chapter 13.
- The chapter 14 `extends` recipe
  (`[env:uno-debug]` inheriting
  `[env:uno]`) was additionally
  exercised in a scratch copy of the
  project and builds successfully;
  the scratch copy was discarded and
  is not a transcript.

**Observed behaviour kept in the
text:** PlatformIO rewriting
`platformio.ini` when installing the
library dropped comments placed
beside the rewritten sections
(chapter 5) — the fixture's file is
reproduced exactly as the tool left
it.

**Documented only, and labelled as
such in the chapters:** uploading
and flashing a real board; the
serial monitor against live hardware
(including the baud-mismatch symptom,
stated from the code's two numbers);
`pio test` on a board; debugging
with a hardware probe; the PlatformIO
IDE (VS Code extension) as an
experience — everything it does is
Core underneath, but its screens were
not exercised; the official installer
script and distribution packages
(chapter 3 names them without having
run them); all platforms other than
`native` and `atmelavr`, including
ESP32-class boards whose toolchains
the lab deliberately did not
download; boards whose upload is a
USB mass-storage copy rather than a
serial protocol; and PlatformIO's
paid Plus services (remote
development, cloud builds), which no
chapter depends on.

**Fixtures:** everything the lab made
up is small and generic — a
running-average library, fixed
simulated readings (21.0–22.1), a
blinking LED. The one registry
library used (ArduinoJson) is public
and pinned. Nothing in the lab is
modelled on any real person,
organisation, board collection or
event.
