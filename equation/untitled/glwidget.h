#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QString>
#include <QDebug>
#include <memory>

#include "renderable.h"
#include "expression/expression.h"

using namespace std;

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_1_Core {
    Q_OBJECT
  public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    Expression expression;

    unique_ptr<Renderable> renderer;
  private:
    GLuint uniform_a;
    GLuint uniform_b;

    QOpenGLShaderProgram* mainShaderProg,* blackShaderProg,* whiteShaderProg,* greyShaderProg;
    void createShaderPrograms();
    void bindShader(QOpenGLShaderProgram *program);

    void renderRenderable(Renderable *obj, QOpenGLShaderProgram*shaderProg, GLenum mode); // Render a renderable objects

};

#endif // GLWIDGET_H
