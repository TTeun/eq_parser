#include "parser.h"

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

}

namespace client
{
  // struct is_num : public boost::static_visitor<bool>
  // {
  //     bool operator()(nil & t) const { return false; }
  //     bool operator()(double & t) const { return true; }
  //     bool operator()(std::string & t) const { return false; }
  //     bool operator()(binary_operation & t) const { return false; }
  //     bool operator()(unary_operation & t) const { return false; }
  // };

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

  // class simplify_visitor {
  // public:
  //   void operator()(nil & t) const {}
  //   void operator()(double & t) const {}
  //   void operator()(std::string & t) const {}
  //   void operator()(binary_operation & t) const {
  //     if ( boost::apply_visitor(is_num(), t.left.type) && boost::apply_visitor(is_num(), t.left.type) ){
  //       if ( t.tag == BIN_OP::ADD )
  //         std::cout << "Hallo";
  //     }
  //   }
  //   void operator()(unary_operation & t) const {}
  // };

  void print_tree(expression &expr){
    std::cout << expr.name << " is a function of: ";
    for (auto &a : expr.arguments)
      std::cout << a << " ";
    std::cout << '\n';

    // boost::apply_visitor(simplify_visitor(), expr.syntax_tree.type);
    // boost::apply_visitor(print_visitor(), expr.syntax_tree.type);
    std::cout << "\n";
  }
}
