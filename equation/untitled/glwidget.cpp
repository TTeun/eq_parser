#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
  :
  QOpenGLWidget(parent),
  renderer(make_unique<Renderable>(this))
{
  qDebug() << "GLWidget constructor";
}

GLWidget::~GLWidget()
{
  qDebug() << "GLWidget destructor";
}

void GLWidget::initializeGL()
{
  qDebug() << "GLWidget init";
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 1.0);

  renderer->registerRenderable();
  createShaderPrograms();
}

void GLWidget::paintGL()
{
  qDebug() << "Paint";
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  renderer->updateRenderable();
  renderRenderable(renderer.get(), mainShaderProg, GL_LINE_STRIP);
}

void GLWidget::resizeGL(int w, int h)
{
  Q_UNUSED(w);
  Q_UNUSED(h);
}

void GLWidget::renderRenderable(Renderable *obj, QOpenGLShaderProgram *shaderProg, GLenum mode)
{
  glBindVertexArray(obj->vao);
  shaderProg->bind();
  glDrawArrays(mode, 0, obj->coords->size());
  glBindVertexArray(0);
  shaderProg->release();
}

void GLWidget::createShaderPrograms()
{
  mainShaderProg = new QOpenGLShaderProgram();
  mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
  mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");
  mainShaderProg->link();
}

