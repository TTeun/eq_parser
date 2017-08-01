#include "expression.h"
#include "../parser/print.h"
#include "../parser/simplify.h"

#include "QDebug"

Expression::Expression() {}

Expression::Expression(QString &str)
{
  parse_equation(str);
}

Expression::~Expression() {}

void Expression::parse_equation(QString const &str)
{
  std::string eq = str.toUtf8().constData();

  std::string::const_iterator iter = eq.begin();
  std::string::const_iterator end = eq.end();

  expr = client::expression();
  bool r = phrase_parse(iter, end, exp_parser{} >> qi::eoi, boost::spirit::ascii::space, expr);
  if (r) {
    client::collapsed_type c = boost::apply_visitor(client::collapse_visitor(), expr.syntax_tree.type);
    if (c.can_collapse)
      expr.syntax_tree.type = c.value;

    state = EXPR_STATE::OK;

    client::print_tree(expr);
  } else {
    state = EXPR_STATE::ERROR;
  }

}
