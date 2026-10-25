# Limits

Stated plainly, as the criteria
require.

**The downloads are large, and they
are per-platform.** This small guide —
one desktop platform, one AVR platform,
a checker, an upload tool — filled
about **300 MB** of core directory.
Each new chip family brings its own
toolchain of similar appetite. On a
slow or metered connection, the first
project for a new board is an
investment, and "offline once fetched"
is the consolation, not a rebuttal.

**The registry is a trust decision.**
`lib_deps` code is compiled into your
firmware with the same rights as your
own. The registry is a commons:
excellent, maintained libraries beside
abandoned ones, with ownership that
can change. Pinning (chapter 8) makes
your choice *reproducible*; it does
not make it *reviewed*. On anything
that matters, read what you fetch —
it is your program now.

**The board is the last metre, and it
is yours.** PlatformIO organises
everything up to the USB lead. It
cannot plug the board in, set its
jumpers, power it correctly, or tell
a dead cable from a dead chip. The
guide's own lab stopped exactly there:
every build proven, the upload an
error message about a port that does
not exist. Chapter 13 teaches the
steps; the steps require your hand.

**Static numbers are not behaviour.**
The flash and RAM lines (chapter 6)
are static accounts. Stack depth,
heap fragmentation on long-running
firmware, timing — the things that
fail at hour nine — are not in any
build report and never will be. The
desktop tests shrink the unknown; they
do not close it.

**The tool rewrites its file.** As
chapter 5 recorded, managing
dependencies means `platformio.ini`
is edited by the tool, and comments
in rewritten sections may be lost.
Version control is the mitigation,
and it is a mitigation, not a fix.

**One guide, two platforms.** The lab
verified `native` and `atmelavr` end
to end. The other platforms —
ESP32, STM32, RP2040 and hundreds
more — follow the same documented
shape, and the transcripts give every
reason to expect them to behave; but
expectation is not verification, and
this guide's criteria notes say which
is which. Their toolchains are also
several times the AVR one's size,
which is why a guide about honest
limits did not pretend otherwise by
downloading them all.

**Core is a Python program**, with a
Python program's dependencies; the
venv of chapter 3 keeps them from
becoming your system's problem, at
the price of one more environment to
remember to activate.
