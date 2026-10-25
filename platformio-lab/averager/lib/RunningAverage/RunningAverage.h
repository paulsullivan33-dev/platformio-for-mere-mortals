#pragma once

// A running average over the most recent readings.
//
// Feed it numbers with add(); average() returns the mean of
// the last `capacity` values (or of everything seen so far,
// if fewer than that have arrived).
class RunningAverage {
public:
    explicit RunningAverage(int capacity);
    ~RunningAverage();

    void add(double value);
    double average() const;
    int count() const;
    void clear();

private:
    double *values_;
    int capacity_;
    int count_;
    int next_;
    double sum_;
};
