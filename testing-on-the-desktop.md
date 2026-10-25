# Testing on the Desktop

Here is the desktop twin's finest hour.
The library's logic — windowing,
averaging, clearing — can be *tested*,
automatically, on your own machine,
with no board involved and none
needed. PlatformIO's vehicle is
`pio test`, and its default framework
is **Unity**, a small unit-test library
for C.

## The tests

Tests live under `test/`, one folder
per suite, and the guide's suite is
four small checks of the promises
chapter 7 made (file
`test/test_running_average/test_main.cpp`
in the lab project):

```cpp
void test_oldest_reading_leaves_the_window(void) {
    RunningAverage avg(3);
    avg.add(1.0);
    avg.add(2.0);
    avg.add(3.0);
    avg.add(10.0);  // pushes the 1.0 out
    TEST_ASSERT_EQUAL_INT(3, avg.count());
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 5.0, avg.average());
}
```

plus the empty average being zero, the
average before the window fills, and
`clear()` starting over. Each test is a
claim about behaviour, stated once, in
code that either proves it on every
run or says so loudly.

## Running them

```bash
pio test -e native
```

Check (transcript `t06`):

```text
test/test_running_average/test_main.cpp:46: test_empty_average_is_zero [PASSED]
test/test_running_average/test_main.cpp:47: test_average_before_window_fills [PASSED]
test/test_running_average/test_main.cpp:48: test_oldest_reading_leaves_the_window [PASSED]
test/test_running_average/test_main.cpp:49: test_clear_starts_over [PASSED]
================== 4 test cases: 4 succeeded ==================
```

What happened under the table: PlatformIO
built the test suite *instead of* the
programs — the test folder's own
`main()`, the project libraries, Unity —
and ran it under the native environment.
Note what it did not need: `arduino_main.cpp`,
the framework, or a `.hex`. Tests are a
third consumer of the library, beside
the two programs, and they are why the
library was kept free of hardware in
the first place. (The lab also watched
Unity itself arrive as a package during
the first board build — the test
framework is a download like any other,
declared by the platform's defaults.)

## Why test on the desktop at all

Because the alternative is testing on
the board, where a failing average
looks like a flickering LED and a vague
serial line, and each trial costs an
upload. On the desktop a hundred
readings cost a millisecond and a
failure names its line number. The
division of labour that falls out of
this is the healthiest habit in the
guide:

- **Logic** — arithmetic, parsing,
  state machines, formatting — lives
  in libraries and is proven by tests
  on the desktop.
- **Hardware contact** — pins, timing,
  the serial line — lives in the thin
  `src/` front ends and is proven by
  the board, in your hand, where such
  proof exists.

Tests can also be *run on the board*
for environments that support it —
`pio test -e uno` uploads a test
firmware and reads results over the
serial line. The lab could not do
that (no board), so this guide labels
it documented-only and tests where it
can: here, where the evidence is.

## Check: break it on purpose once

Before trusting a suite, watch it fail:
change one expected value, rerun, and
see the red line name the test. A suite
you have never seen fail is a smoke
alarm you have never tested. The
transcripts keep only the passing run;
the failure rehearsal is yours to do,
once, on purpose.
