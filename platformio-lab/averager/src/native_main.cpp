// The desktop twin of the board program: the same library,
// the same simulated readings, printed to the terminal
// instead of a serial line. Runs under the "native" env.
#include <cstdio>

#include <ArduinoJson.h>

#include "RunningAverage.h"
#include "settings.h"

// A fixed set of readings, in tenths of a degree, standing
// in for a sensor so the output is the same on every run.
static const double readings[] = {21.0, 21.4, 20.9, 21.8, 22.1, 21.7};

int main() {
    RunningAverage avg(SAMPLE_COUNT);
    int samples = 0;
    for (double r : readings) {
        avg.add(r);
        ++samples;
        std::printf("reading %.1f -> average of last %d: %.2f\n",
                    r, avg.count(), avg.average());
    }

    // The same summary as a line of JSON, the shape a
    // logger would append to a file. ArduinoJson is a
    // library from the PlatformIO registry (chapter 8).
    JsonDocument doc;
    doc["samples"] = samples;
    doc["window"] = SAMPLE_COUNT;
    doc["average"] = avg.average();
    char line[128];
    serializeJson(doc, line, sizeof(line));
    std::printf("%s\n", line);
    return 0;
}
