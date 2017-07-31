#ifndef SIMPLIFY__H
#define SIMPLIFY__H

#include "parser.h"

namespace client {
  struct num_type {
    num_type()
      : is_double(false)
    {}
    num_type(double _value)
      : value(_value), is_double(true)
    {}

    operator bool(){ return is_double; }
    bool is_double = false;
    double value = 0.0;
  };

  struct num_visitor : public boost::static_visitor<num_type>
    {
        num_type operator()(nil & t) const;
        num_type operator()(double & t) const;
        num_type operator()(std::string & t) const;
        num_type operator()(binary_operation & t) const;
        num_type operator()(unary_operation & t) const;
    };

    struct collapsed_type {
      collapsed_type()
        : can_collapse(false)
      {}
      collapsed_type(double _value)
        : value(_value), can_collapse(true)
      {}

      bool can_collapse = false;
      double value = 0.0;
    };

    struct collapse_visitor : public boost::static_visitor<collapsed_type> {
    public:
      collapsed_type operator()(nil & t) const;
      collapsed_type operator()(double & t) const;
      collapsed_type operator()(std::string & t) const;
      collapsed_type operator()(binary_operation & t) const;
      collapsed_type operator()(unary_operation & t) const;
    };

}

#endif
