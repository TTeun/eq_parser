#include "parser.h"
#include "simplify.h"

namespace client
{
  ast& ast::operator+=(ast const& rhs){
    type = binary_operation(BIN_OP::ADD, type, rhs);
    return *this;
  }

  ast& ast::operator-=(ast const& rhs){
    type = binary_operation(BIN_OP::SUB, type, rhs);
    return *this;
  }

  ast& ast::operator*=(ast const& rhs){
    type = binary_operation(BIN_OP::MUL, type, rhs);
    return *this;
  }

  ast& ast::operator/=(ast const& rhs){
    type = binary_operation(BIN_OP::DIV, type, rhs);
    return *this;
  }

  ast& ast::operator^=(ast const& rhs){
    type = binary_operation(BIN_OP::POW, type, rhs);
    return *this;
  }

}

namespace client
{
  class print_visitor {
  public:
    void operator()(nil & t) const { std::cout << "ERROR";  }
    void operator()(double & t) const { std::cout << t;  }
    void operator()(std::string & t) const { std::cout << t;  }
    void operator()(binary_operation & t) const {
      std::cout << "(";
      boost::apply_visitor(*this, t.left.type);
      std::cout << (
                    t.tag == BIN_OP::ADD ? "+" :
                    t.tag == BIN_OP::SUB ? "-" :
                    t.tag == BIN_OP::MUL ? "*" :
                    t.tag == BIN_OP::DIV ? "/" :
                    t.tag == BIN_OP::POW ? "^" :
                    "empty"
                   );
      boost::apply_visitor(*this, t.right.type);
      std::cout << ")";
    }
    void operator()(unary_operation & t) const {
      std::cout << (
                    t.tag == UN_OP::MIN ? "-("   :
                    t.tag == UN_OP::SIN ? "sin(" :
                    t.tag == UN_OP::COS ? "cos(" :
                    t.tag == UN_OP::TAN ? "tan(" :
                    "empty("
                   );
      boost::apply_visitor(*this, t.tree.type);
      std::cout << ")";
    }
  };

  void print_tree(expression &expr){
    std::cout << expr.name << " is a function of: ";
    for (auto &a : expr.arguments)
      std::cout << a << " ";
    std::cout << '\n';

    collapsed_type c = boost::apply_visitor(collapse_visitor(), expr.syntax_tree.type);
    if (c.can_collapse)
      expr.syntax_tree.type = c.value;

    boost::apply_visitor(print_visitor(), expr.syntax_tree.type);
    std::cout << "\n";
  }
}
