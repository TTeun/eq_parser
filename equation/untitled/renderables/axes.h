#ifndef AXES_H
#define AXES_H

#include <memory>
#include "renderable.h"

using namespace std;

class GLWidget;

class Axes {
  public:
    Axes(GLWidget *ui);

    void registerAxes();

    Renderable *x_axis();
    Renderable *y_axis();

  private:
    unique_ptr<Renderable> x_axis_m;
    unique_ptr<Renderable> y_axis_m;
};

#endif // AXES_H
