# Installing PlatformIO

There are three common ways in. This
guide teaches the first, because it is
the one the lab verified and the one
that behaves identically on Linux,
Windows and macOS.

## The way the lab did it: pip in a venv

PlatformIO Core is a Python program, so
the clean install is a Python **virtual
environment** — a private folder of
Python packages that cannot quarrel with
anything else on the machine:

```bash
python3 -m venv ~/platformio-venv
~/platformio-venv/bin/pip install platformio
~/platformio-venv/bin/pio --version
```

Check:

```text
PlatformIO Core, version 6.2.0
```

(transcript `t00`). That is the whole
install. Core's own downloads — platforms,
toolchains, libraries — do not arrive
yet; they come later, per project, the
first time a build needs them. On
Windows the same three steps work with
`py -m venv` and
`Scripts\pio.exe` in place of `bin/pio`.

Two habits worth starting with:

- **Use the venv's `pio` by full path, or
  activate the venv** (`. ~/platformio-venv/bin/activate`)
  so plain `pio` works. Examples in this
  guide write plain `pio` and assume one
  of the two.
- **Know where the downloads go.** By
  default Core keeps platforms and
  packages in `~/.platformio`. Setting
  the environment variable
  `PLATFORMIO_CORE_DIR` moves that store;
  the lab pointed it into its workspace
  (`PLATFORMIO_CORE_DIR=~/workspace/platformio-lab/core`)
  so the whole experiment — and its
  300 MB — could be measured and deleted
  as one folder. At home, the default is
  fine; just know the address.

## The other ways in

- **The official installer script** —
  PlatformIO publishes a `get-platformio.py`
  that builds the same venv for you in
  `~/.platformio/penv`. Same engine, less
  typing, one more moving part to trust.
- **PlatformIO IDE** — an extension for
  VS Code that installs Core on first
  launch and adds buttons, a board
  explorer and a serial monitor pane.
  If you already live in that editor it
  is the comfortable route. It is
  documented-only in this guide: the lab
  had no editor, and everything the IDE
  does can be done with the commands in
  these chapters, which is rather the
  point of learning them.
- **A system package** — some Linux
  distributions package PlatformIO. It
  tends to lag the official release and
  to split files in distro-specific
  ways; the pip route above is the one
  the documentation supports.

## The udev footnote, Linux only

On Linux, talking to a board over USB
needs permission. PlatformIO's installer
materials point at a `99-platformio-udev.rules`
file for `/etc/udev/rules.d/`; without
it, uploads can fail with permission
errors even when everything else is
right. The lab met the warning text
itself (transcript `t08`) but had no
board to test the remedy against, so the
guide states the rule plainly and claims
no more: on a real machine, install the
rules file when the warning appears.

## Check: what you have now

`pio --version` answers, and nothing
else has been downloaded. Disk used so
far: the venv, about 30 MB. Every further
byte in this guide arrives under a named
platform or package, in a transcript,
where you can watch it happen.
