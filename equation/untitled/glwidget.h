#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "parser/parser.h"

class GLWidget : public QGLWidget
{
  Q_OBJECT
public:
  explicit GLWidget(QWidget *parent = 0);


  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);


  using boost::spirit::ascii::space;
  typedef std::string::const_iterator iterator_type;
  typedef client::exp_parser<iterator_type> exp_parser;

  exp_parser g;

};

#endif // GLWIDGET_H
