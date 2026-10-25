# Uploading and the Monitor

Everything so far happened on your
desk. This chapter is about the last
metre: the finished firmware travelling
into a real board, and the board
talking back. **It is the guide's
documented-only chapter** — the lab
machine had no board attached — and
it says so on its face. What it can
offer is the shape of the steps, the
settings that control them, and
something rarer in print: the *real*
output of these commands when there is
no board, which is the first thing
every new user meets and the thing
documentation usually skips.

## Uploading: `pio run -t upload`

```bash
pio run -e uno -t upload
```

With a board on a USB lead, PlatformIO
builds (or reuses) the firmware, finds
the board's serial port, and hands the
`.hex` to the platform's upload tool —
for the Uno, `avrdude`, speaking the
Arduino bootloader protocol. The
settings that steer it live in the
environment:

- `upload_port` — which serial device
  (e.g. `/dev/ttyACM0`, `COM3`). Left
  unset, PlatformIO looks for a known
  board and complains if it cannot
  find one.
- `upload_speed` — the bootloader's
  baud rate, normally set by the board
  definition itself.
- `upload_protocol` — how the tool
  talks; again, the board definition
  usually knows.

First, find out whether the machine
sees a board at all:

```bash
pio device list
```

In the lab, that command printed
nothing at all — an empty list is a
result — and the upload then did
something genuinely helpful
(transcript `t08`): it downloaded
`tool-avrdude`, rebuilt the firmware,
reported its size — and stopped at
"Looking for upload port…" with:

```text
Error: Please specify `upload_port` for environment
or use global `--upload-port` option.
```

That error, on a real desk, reads as a
checklist: is the board plugged in, is
it the kind of board that presents a
serial port, on Linux are the udev
rules installed (the same transcript
carries that warning), and if the board
*is* listed by `pio device list`, does
`upload_port` name it? The failure is
the tool declining to guess — the
correct behaviour when the alternative
is flashing whatever answered first.

## The monitor: `pio device monitor`

The board's half of the conversation —
the `Serial.print` lines in the guide's
`arduino_main.cpp` — is read with the
serial monitor:

```bash
pio device monitor -e uno
```

The `-e` matters: the monitor takes
its speed from the environment's
`monitor_speed` (9600 in the guide's
file, chosen to match the program's
`Serial.begin(9600)` — a mismatch
between those two numbers is the
classic cause of a screen of garbage
characters, and it is a mismatch, not
a mystery). Leave with Ctrl-C. Filters
exist for timestamps and for decoding
odd output; the plain monitor is the
one to learn first.

What would the guide's board print?
From the code, every second:

```text
average of last 3: 21.10
```

— the sentence is certain, because
the same library produced it on the
desktop; the LED's blink and the
serial line's arrival in your hand
are the parts only a board can prove,
and this guide does not pretend
otherwise.

## Check: know your no-board state

Run `pio device list` on your machine
*before* the board first arrives.
Knowing exactly what "nothing
attached" looks like — the empty
list, the upload's parting error —
turns the day it does arrive into a
comparison instead of an
investigation.
