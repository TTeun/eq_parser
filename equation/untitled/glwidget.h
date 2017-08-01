#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
#include <QString>
#include <QDebug>

#include "expression/expression.h"

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_1_Core
{
  Q_OBJECT
public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  Expression expr;

};

#endif // GLWIDGET_H
