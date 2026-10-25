#pragma once

// How many readings the running average keeps.
// A build flag (-DSAMPLE_COUNT=8) overrides this default,
// which is how the guide proves build flags reach the code.
#ifndef SAMPLE_COUNT
#define SAMPLE_COUNT 4
#endif
