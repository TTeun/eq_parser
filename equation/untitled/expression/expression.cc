#include "expression.h"
#include "../parser/print.h"
#include "../parser/simplify.h"

#include <cassert>
#include <QDebug>

LinearSpan Expression::span{-1, 1, 100};

Expression::Expression()
  :
  var_map(make_unique<std::unordered_map<std::string, double>>())
{}

Expression::Expression(QString &str)
  :
  var_map(make_unique<std::unordered_map<std::string, double>>())
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

//    client::print_tree(expr);
  } else {
    state = EXPR_STATE::ERROR;
  }

}

double Expression::eval_at(string &var, double _x)
{
  assert(state == EXPR_STATE::OK);

  if (var_map->find(var) != var_map->end())
    (*var_map)[var] = _x;
  else
    var_map->insert(make_pair(var, _x));

  client::expression e = expr;
  client::collapsed_type c = boost::apply_visitor(client::collapse_visitor(var_map.get()), e.syntax_tree.type);
  if (c.can_collapse)
    return c.value;
  else
    return -100.0;
}

size_t Expression::dimension()
{
  return expr.arguments.size();
}

bool Expression::is_ok()
{
  return state == EXPR_STATE::OK;
}
