#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
#include <QString>
#include <QDebug>
#include "parser/parser.h"

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_1_Core
{
  Q_OBJECT
public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();

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
