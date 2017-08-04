#ifndef AXES_H
#define AXES_H

#include <memory>
#include "renderable.h"

#include "../expression/linearspan.h"

using namespace std;

class GLWidget;

class Axes {
  public:
    Axes(GLWidget *ui);

    void registerAxes();
    void set_domain(double x_min, double x_max);
    void set_range(double y_min, double y_max);

    Renderable *x_axis();
    Renderable *y_axis();

    static LinearSpan domain;
    static Range range;

  private:
    unique_ptr<Renderable> x_axis_m;
    unique_ptr<Renderable> y_axis_m;
};

#endif // AXES_H
