#ifndef RANGE_H
#define RANGE_H

class Range {
  public:
    Range();
    Range(double min, double max);

    void incr(double dy);
    double min();
    double max();
    void set_min(double _min);
    void set_max(double _max);

  protected:
    double min_m = -1;
    double max_m = 1;
};

#endif // RANGE_H
