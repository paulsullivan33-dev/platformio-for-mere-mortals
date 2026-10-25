// The board program: blink the built-in LED and report a
// running average of simulated readings over the serial
// line. Built by the "uno" env; never uploaded in the lab
// (there is no board), so what you see in the guide is the
// build, not a run.
#include <Arduino.h>

#include "RunningAverage.h"
#include "settings.h"

static RunningAverage avg(SAMPLE_COUNT);
static const double readings[] = {21.0, 21.4, 20.9, 21.8, 22.1, 21.7};
static const int readingCount =
    sizeof(readings) / sizeof(readings[0]);
static int nextReading = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    avg.add(readings[nextReading]);
    nextReading = (nextReading + 1) % readingCount;

    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("average of last ");
    Serial.print(avg.count());
    Serial.print(": ");
    Serial.println(avg.average());
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(750);
}
