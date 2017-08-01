#include "linearspan.h"

LinearSpan::LinearSpan()
{
  a = -1;
  b = 1;
}

LinearSpan::LinearSpan(double _a, double _b, size_t _n)
  : a(_a), b(_b), n(_n)
{}

size_t LinearSpan::size()
{
  return n + 1;
}

double LinearSpan::value_at_pos(size_t i)
{
  return (a + i * (b - a) / static_cast<double>(n));
}

void LinearSpan::set_a(double _a)
{
  a = _a;
}

void LinearSpan::set_b(double _b)
{
  b = _b;
}

void LinearSpan::set_n(size_t _n)
{
  n = _n;
}

double LinearSpan::get_a()
{
  return a;
}

double LinearSpan::get_b()
{
  return b;
}
