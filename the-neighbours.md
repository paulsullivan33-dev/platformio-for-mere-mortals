# The Neighbours

PlatformIO is one answer to "how do I
build for boards." These are the
others you will meet, and what each
trades.

## The Arduino IDE

The friendly face of board programming:
pick a board, pick a port, press the
arrow. For a first blink it cannot be
beaten, and its library manager taught
the world the shape of the problem.
What it trades away is the file: board
settings, library versions and options
live in the editor's state and your
memory, sketches are single-program
affairs, and there is no desktop twin,
no test runner, no second machine
story. Many people start here and
arrive at PlatformIO (or the next
entry) carrying a sketch — which the
Arduino *framework* setting welcomes
unchanged, as this guide's Uno build
shows.

## The Arduino CLI

Arduino's own command line:
`arduino-cli compile --fqbn ...`,
with libraries and boards managed in
its own config. It does honestly most
of what this guide does for Arduino
boards specifically — reproducible-ish
builds, scriptability — with a
smaller download and a narrower
world: Arduino cores only, a thinner
library-versioning story, no native
test environment of the same shape.

## The vendor frameworks: ESP-IDF, STM32Cube, Zephyr

Each chip family also offers its own
house toolchain — Espressif's ESP-IDF,
ST's Cube, the Linux Foundation's
Zephyr RTOS. They go deeper than
PlatformIO can: the newest chip
features first, the vendor's own
debuggers and examples, support
contracts. The trade is scope and
portability: learn ESP-IDF and you
know ESP32, in depth, and nothing
else transfers except the C. Notably,
PlatformIO can sit *on top* of several
of them — `framework = espidf` is a
real configuration — acting as the
fetching-and-organising layer over
the vendor's own build, which is
perhaps the clearest statement of what
PlatformIO itself is.

## Plain Make and CMake

The ancestors: a hand-written build
file naming the cross-compiler, the
flags, the sources. Total control,
nothing downloaded behind your back,
and every problem in this guide —
finding toolchains, pinning libraries,
adding a board, testing on the desk —
reappearing as *your* problem, in
your file, forever. Right for a team
that already has that expertise and a
reason; a heavy way to blink an LED.

## MicroPython and CircuitPython

A different answer entirely: put a
Python interpreter *on* the board and
skip compiling — copy a `.py` file
across, and it runs. For learning,
sensors-and-scripting projects, and
anything that changes hourly, it is
delightful and this shelf's MicroPython
guide covers it. The trades are speed,
memory (the interpreter lives in the
same kilobytes your program wanted),
and a ceiling you meet the day the
project needs a library that exists
only in C — at which point the road
leads back here.

## Check: the choosing question

Ask of any project: *how many boards,
how long a life, how many machines
must rebuild it?* One board, one
afternoon, one laptop — the IDE is
honestly enough. Anything past that,
the project file starts paying rent —
and that rent is the subject of this
guide.
