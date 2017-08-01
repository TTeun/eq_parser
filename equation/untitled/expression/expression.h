#ifndef EXPRESSION__H
#define EXPRESSION__H

#include <QString>
#include <unordered_map>
#include <string>
#include <memory>

#include "../parser/parser.h"

using namespace std;

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

    double eval_at(string &var, double _x);
    size_t dimension();

  private:
    EXPR_STATE state = EXPR_STATE::EMPTY;
    std::unique_ptr<std::unordered_map<std::string, double>> var_map;
    //    var_map->insert(make_pair(std::string("x"), 1.0));

};



#endif
