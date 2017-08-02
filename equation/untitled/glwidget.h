#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QString>
#include <QDebug>
#include <memory>

#include "renderables/renderable.h"
#include "expression/expression.h"
#include "renderables/axes.h"

class MainWindow;

using namespace std;

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_1_Core {
    Q_OBJECT
  public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    friend class MainWindow;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    unique_ptr<Renderable> renderer;
    unique_ptr<Expression> expression;
    unique_ptr<Axes> axes;

  protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    double x_click, y_click;

  signals:
    void linear_span_changed(double a, double b);

  private:
    GLuint uniform_a;
    GLuint uniform_b;

    unique_ptr<QOpenGLShaderProgram> mainShaderProg;
    void createShaderPrograms();
    void bindShader(QOpenGLShaderProgram *program);
    void update_linear_span(double dx, double dy);
    void renderRenderable(Renderable *obj, QOpenGLShaderProgram*shaderProg, GLenum mode); // Render a renderable objects

};

#endif // GLWIDGET_H
