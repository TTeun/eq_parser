#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "linearspan.h"
#include "expression.h"
#include "../renderable.h"

namespace evaluator {
  void fill_expr_1D(Expression &expr, Renderable *renderer);
}

#endif // EVALUATOR_H
