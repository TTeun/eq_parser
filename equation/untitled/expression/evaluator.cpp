#include "evaluator.h"
#include <QDebug>
#include <string>

namespace evaluator {

  void fill_expr_1D(Expression &expression, Renderable *renderer)
  {
    if (expression.dimension() > 1 || not expression.is_ok()) {
      qDebug() << "Evaluating expression as 1D but has more variables";
      return;
    }

    renderer->clear();
    qDebug() << "Filling renderable with expression";
    std::string var = expression.expr.arguments[0];

    for (size_t i = 0; i < Expression::span.size(); ++i) {
      double x = Expression::span.value_at_pos(i);
      double y = expression.eval_at(var, x );
//      qDebug() << "(" <<  x << "," << y << ")";

      renderer->coords->append( QVector2D( x, y ) );
      renderer->colours->append(QVector3D(0.0, 0.0, 0.0));
    }
  }

}
