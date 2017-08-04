#ifndef LINEARSPAN_H
#define LINEARSPAN_H

#include <cstddef>
#include "range.h"

class LinearSpan : public Range {
  public:
    LinearSpan();
    LinearSpan(double _min, double _max, size_t _n);

    size_t size();
    double value_at_pos(size_t i);

    void set_n(size_t n);

  private:
    size_t n = 100;  // Number of segments
};

#endif // LINEARSPAN_H
