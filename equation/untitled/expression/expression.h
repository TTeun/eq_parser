#ifndef EXPRESSION__H
#define EXPRESSION__H

#include <QString>

#include "../parser/parser.h"

class Expression {
public:
  Expression();
  Expression(QString &str);
  ~Expression();


  enum class EXPR_STATE {
    EMPTY,
    OK,
    ERROR
  };

  void parse_equation(QString const &str);

  typedef std::string::const_iterator iterator_type;
  typedef client::exp_parser<iterator_type> exp_parser;

  static exp_parser g;
  client::expression expr;


private:
  EXPR_STATE state = EXPR_STATE::EMPTY;
};



#endif
