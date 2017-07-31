#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{

}

void GLWidget::initializeGL(){
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL(){
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glClearColor(0.2, 0.0, 0.0, 1.0);

}

void GLWidget::resizeGL(int w, int h){
  Q_UNUSED(w);
  Q_UNUSED(h);
}
