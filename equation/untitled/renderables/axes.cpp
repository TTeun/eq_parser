#include "axes.h"

#include "../glwidget.h"

LinearSpan Axes::domain{-1, 1, 5000};
Range Axes::range{};

Axes::Axes(GLWidget *ui)
  :
  x_axis_m(make_unique<Renderable>(ui)),
  y_axis_m(make_unique<Renderable>(ui))
{
  x_axis_m->coords->append(QVector2D(-1.0, 0.0));
  x_axis_m->coords->append(QVector2D(1.0, 0.0));

  x_axis_m->colours->append(QVector3D(0.75, 0.75, 0.75));
  x_axis_m->colours->append(QVector3D(0.75, 0.75, 0.75));

  y_axis_m->coords->append(QVector2D(0.0, -1.0));
  y_axis_m->coords->append(QVector2D(0.0, 1.0));

  y_axis_m->colours->append(QVector3D(0.75, 0.75, 0.75));
  y_axis_m->colours->append(QVector3D(0.75, 0.75, 0.75));
}

void Axes::registerAxes()
{
  x_axis_m->registerRenderable();
  y_axis_m->registerRenderable();
}

void Axes::set_domain(double x_min, double x_max)
{
  (*x_axis()->coords)[0] = QVector2D(x_min, 0.0);
  (*x_axis()->coords)[1] = QVector2D(x_max, 0.0);
}

void Axes::set_range(double y_min, double y_max)
{
  (*y_axis()->coords)[0] = QVector2D(0.0, y_min);
  (*y_axis()->coords)[1] = QVector2D(0.0, y_max);
}

Renderable *Axes::x_axis()
{
  return x_axis_m.get();
}

Renderable *Axes::y_axis()
{
  return y_axis_m.get();
}

