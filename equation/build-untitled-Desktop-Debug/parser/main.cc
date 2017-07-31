#include "parser.h"

#include <iostream>
#include <vector>
#include <string>

int main(){
  using boost::spirit::ascii::space;
  typedef std::string::const_iterator iterator_type;
  typedef client::exp_parser<iterator_type> exp_parser;
  exp_parser g;

  client::expression expr;
  std::string str;
  getline(std::cin, str);
  std::string::const_iterator iter = str.begin();
  std::string::const_iterator end = str.end();

  bool r = phrase_parse(iter, end, exp_parser{} >> qi::eoi, space, expr);
  if (r)
    print_tree(expr);
  else
    std::cout << "Parse failed\n";
}
