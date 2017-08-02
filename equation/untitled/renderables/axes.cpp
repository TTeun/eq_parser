#include "axes.h"

#include "../glwidget.h"

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

void Axes::set_ab(double a, double b)
{
  (*x_axis()->coords)[0] = QVector2D(a, 0.0);
  (*x_axis()->coords)[1] = QVector2D(b, 0.0);
}

Renderable *Axes::x_axis()
{
  return x_axis_m.get();
}

Renderable *Axes::y_axis()
{
  return y_axis_m.get();
}

