#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QString>
#include <QDebug>
#include "parser/parser.h"


using boost::spirit::ascii::space;

class GLWidget : public QGLWidget
{
  Q_OBJECT
public:
  explicit GLWidget(QWidget *parent = 0);


  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);


  void parse_equation(QString const &str);

  typedef std::string::const_iterator iterator_type;
  typedef client::exp_parser<iterator_type> exp_parser;
  exp_parser g;
  client::expression expr;

};

#endif // GLWIDGET_H
