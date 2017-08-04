#include "linearspan.h"

LinearSpan::LinearSpan()
  : Range(-1, 1)
{
  n = 100;
}

LinearSpan::LinearSpan(double _min, double _max, size_t _n)
  :
  Range(_min, _max),
  n(_n)
{}

size_t LinearSpan::size()
{
  return n + 1;
}

double LinearSpan::value_at_pos(size_t i)
{
  return (min_m + i * (max_m - min_m) / static_cast<double>(n));
}


void LinearSpan::set_n(size_t _n)
{
  n = _n;
}

