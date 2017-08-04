#include "evaluator.h"
#include <QDebug>
#include <string>

namespace evaluator {

  void fill_expr_1D(Expression *expression, Renderable *renderer)
  {
    renderer->clear();
    if (expression->dimension() > 1 || not expression->is_ok()) {
      qDebug() << "Evaluating expression as 1D but has more variables";
      return;
    }

    renderer->coords->reserve(Axes::domain.size());
    qDebug() << "Filling renderable with expression";
    std::string var ;

    if (expression->dimension() != 0)
      var = expression->expr.arguments[0];
    else
      var = "d"; // dummy variable for constant function

    for (size_t i = 0; i < Axes::domain.size(); ++i) {
      double x = Axes::domain.value_at_pos(i);
      double y = expression->eval_at(var, x );
//      qDebug() << "(" <<  x << "," << y << ")";

      renderer->coords->append( QVector2D( x, y ) );
      renderer->colours->append(QVector3D(0.0, 0.0, 0.0));
    }
  }

}
