#include "range.h"

Range::Range()
{}

Range::Range(double min, double max)
  : min_m(min), max_m(max)
{}

void Range::incr(double dy)
{
  min_m += dy;
  max_m += dy;
}

double Range::min()
{
  return min_m;
}

double Range::max()
{
  return max_m;
}

void Range::set_min(double _min)
{
  min_m = _min;
}

void Range::set_max(double _max)
{
  max_m = _max;
}
