#ifndef LINEARSPAN_H
#define LINEARSPAN_H

#include <cstddef>

class LinearSpan {
  public:
    LinearSpan();
    LinearSpan(double _a, double _b, size_t _n);

    size_t size();
    double value_at_pos(size_t i);

    void set_a(double _a);
    void set_b(double _b);
    void set_n(size_t n);

    void incr_x(double dx);
    double get_a();
    double get_b();

  private:
    double a;        // Leftmost value of interval
    double b;        // Rightmost value of interval
    size_t n = 100;  // Number of segments
};

#endif // LINEARSPAN_H
