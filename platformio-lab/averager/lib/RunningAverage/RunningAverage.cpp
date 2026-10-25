#include "RunningAverage.h"

RunningAverage::RunningAverage(int capacity)
    : values_(new double[capacity]), capacity_(capacity),
      count_(0), next_(0), sum_(0.0) {
    for (int i = 0; i < capacity_; ++i) {
        values_[i] = 0.0;
    }
}

RunningAverage::~RunningAverage() { delete[] values_; }

void RunningAverage::add(double value) {
    if (count_ == capacity_) {
        sum_ -= values_[next_];  // the oldest reading leaves
    } else {
        ++count_;
    }
    values_[next_] = value;
    sum_ += value;
    next_ = (next_ + 1) % capacity_;
}

double RunningAverage::average() const {
    return count_ == 0 ? 0.0 : sum_ / count_;
}

int RunningAverage::count() const { return count_; }

void RunningAverage::clear() {
    count_ = 0;
    next_ = 0;
    sum_ = 0.0;
}
