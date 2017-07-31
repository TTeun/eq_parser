#include "simplify.h"

namespace client {

  num_type num_visitor::operator()(nil & t) const { return num_type(); }
  num_type num_visitor::operator()(double & t) const { return num_type(t); }
  num_type num_visitor::operator()(std::string & t) const { return num_type(); }
  num_type num_visitor::operator()(binary_operation & t) const { return num_type(); }
  num_type num_visitor::operator()(unary_operation & t) const { return num_type(); }

  double get_val(double l, double r, BIN_OP t){
    switch (t) {
      case BIN_OP::ADD:
        return l + r;
        break;
      case BIN_OP::SUB:
        return l - r;
        break;
      case BIN_OP::MUL:
        return l * r;
        break;
      case BIN_OP::DIV:
        return l / r;
        break;
    }
  }


  collapsed_type collapse_visitor::operator()(nil & t) const {
    return collapsed_type();
   }
  collapsed_type collapse_visitor::operator()(double & t) const {
    return collapsed_type();
   }
  collapsed_type collapse_visitor::operator()(std::string & t) const {
    return collapsed_type();
   }
  collapsed_type collapse_visitor::operator()(binary_operation & t) const {
    num_type left = boost::apply_visitor(num_visitor(), t.left.type);
    num_type right = boost::apply_visitor(num_visitor(), t.right.type);
    if (left && right)
      return collapsed_type(get_val(left.value, right.value, t.tag));

    return collapsed_type();
  }
  collapsed_type collapse_visitor::operator()(unary_operation & t) const {
    return collapsed_type();
  }


}
