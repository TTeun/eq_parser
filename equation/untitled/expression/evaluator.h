#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "expression.h"
#include "../renderables/axes.h"
#include "../renderables/renderable.h"

namespace evaluator {
  void fill_expr_1D(Expression *expr, Renderable *renderer);
}

#endif // EVALUATOR_H
