# Your Own Libraries

Sooner or later a piece of your program
outgrows the program: it has a clear job,
clear edges, and a second program wants
it. PlatformIO's answer is the `lib/`
folder. A folder inside `lib/` *is* a
library — the LDF finds it, compiles it
for whichever environment is building,
and offers its headers to your code.
No registration, no publishing, no
ceremony.

## The guide's library

The averager's arithmetic lives in
`lib/RunningAverage/`:

```text
lib/RunningAverage/
├── RunningAverage.h     the promise
├── RunningAverage.cpp   the work
└── library.json         the name tag
```

The split is the classic C++ one, and
it matters more on boards than on
desktops: the header is what other code
`#include`s; the implementation is
compiled once per environment and
archived (`libRunningAverage.a` in the
build transcripts) for the linker.

The class itself is deliberately plain:
a small ring buffer that remembers the
last *capacity* readings and returns
their mean. Two details in it are the
embedded world in miniature — memory is
allocated once, in the constructor,
rather than as readings arrive; and
asking for the average of nothing
returns 0 rather than dividing by
zero, a choice the unit tests in
chapter 11 pin down.

## library.json — small file, real job

```json
{
    "name": "RunningAverage",
    "version": "1.0.0",
    "description": "A running average over the most recent sensor readings.",
    "keywords": "average, sensor, statistics",
    "authors": [
        { "name": "Averager Contributors", "maintainer": true }
    ],
    "license": "MIT",
    "frameworks": "*",
    "platforms": "*"
}
```

For a private library the manifest is
nearly optional — the folder alone
would be found. Write it anyway, for
three reasons. It gives the library a
**name and version** that appear in
build output (`RunningAverage @ 1.0.0`
in every Dependency Graph), so a
transcript tells you what was built.
Its `frameworks` and `platforms` fields
let the LDF *refuse* the library for an
environment it cannot serve, instead of
failing mid-compile with a stranger's
error. And it is the same manifest the
registry expects (chapter 8), so the
day this library is worth publishing,
it is already dressed.

## One library, two programs

The payoff is already visible in the
lab's transcripts. The *same*
`lib/RunningAverage/` folder was
compiled twice: by the host compiler
into the desktop twin, and by the AVR
cross-compiler into the Uno firmware.
No code changed between the two builds
— the library knows nothing about
screens, serial ports or LEDs; it knows
readings and averages. That ignorance
is the design rule worth stealing:

> Keep hardware in the programs, and
> keep the programs' *thinking* in
> libraries that would compile anywhere.

The programs in `src/` are thin on
purpose: one prints to a terminal, one
blinks an LED and prints to a serial
line. Everything they agree on lives
in the library, where chapter 11 can
test it without either of them.

## Check: prove the sharing

Search both build transcripts (`t02`,
`t04`) for `RunningAverage`. Each
contains its own compile and archive
lines for the same sources — one
library, two toolchains, zero edits.
That is the entire argument for `lib/`,
made by the build itself.
