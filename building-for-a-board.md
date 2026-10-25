# Building for a Board

The desktop twin proved the code. This
chapter performs the build the whole
exercise exists for: the same library,
compiled for an Arduino Uno — a chip
with a different processor, a different
compiler, and roughly the computing
power of a 1980s home computer.

```bash
pio run -e uno
```

## What the build does, in order

(transcript `t04`; condensed)

1. **Resolves the platform.** `[env:uno]`
   asks for `atmelavr` and board `uno`;
   Core prints what that means in
   hardware, and does not exaggerate:
   `ATMEGA328P 16MHz, 2KB RAM, 31.50KB Flash`.
2. **Checks the packages.** Platform,
   toolchain and framework were fetched
   when the project was created
   (chapter 4), so this build downloads
   nothing. On a machine where the
   project is fresh, they arrive now,
   once.
3. **Finds the libraries.** The LDF
   reads the sources, sees
   `RunningAverage.h`, and builds the
   Dependency Graph: just
   `RunningAverage @ 1.0.0`, the private
   library. (The registry library from
   chapter 8 belongs to the native
   environment only, so the Uno build
   neither fetches nor compiles it —
   environments are separate worlds
   that share sources, not builds.)
4. **Compiles everything.** Your
   program, the library, and the whole
   Arduino framework — twenty-odd files
   of it — each becoming an AVR object
   file, then archived and linked into
   `firmware.elf`.
5. **Reports the fit, in the board's own
   units:**

```text
RAM:   [=         ]  13.1% (used 268 bytes from 2048 bytes)
Flash: [==        ]  15.1% (used 4864 bytes from 32256 bytes)
```

6. **Emits the firmware** in the form
   upload tools speak: `.pio/build/uno/firmware.hex`,
   beside the `.elf`.

## Reading the size report like you mean it

Those two lines are the board build's
whole quality gate, and they deserve a
slow read:

- **Flash** is where the program lives
  when power is off. 4,864 of 32,256
  bytes: the framework is most of it;
  your code and the library are the
  margin. When a growing project crosses
  100%, this line is where you find out
  — at build time, on your desk, not at
  upload time at the workbench.
- **RAM** is working space: variables,
  buffers, the stack. 268 of 2,048
  bytes counted *statically*. What the
  report cannot see is runtime appetite
  — a stack that grows in a deep call,
  a buffer filled by input. Treat a
  comfortable static number as necessary,
  not sufficient, and treat anything
  over ~75% as a design smell on a chip
  this small.

Notice too what "release mode" hides:
the build's per-file compile lines are
the record of what actually went in.
When a firmware behaves as if code is
missing, this transcript — which files
were compiled for *this* environment —
is the first place to look, ahead of
the source you *meant* to include
(chapter 9's source filters are the
usual explanation).

## Check: the proof on disk

```bash
ls -la .pio/build/uno/
```

shows `firmware.elf` and `firmware.hex`,
built from your sources by a compiler
for a chip that is not in the room.
That file is the deliverable of the
whole toolchain story: chapter 13 is
about the last metre it travels, down
a USB lead, into an actual board.
