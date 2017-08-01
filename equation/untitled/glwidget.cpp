#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
  :
  QOpenGLWidget(parent),
  renderer(make_unique<Renderable>(this)),
  expression(make_unique<Expression>()),
  mainShaderProg(make_unique<QOpenGLShaderProgram>())
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

void GLWidget::createShaderPrograms()
{
  mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
  mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");
  mainShaderProg->link();

  uniform_a = glGetUniformLocation(mainShaderProg->programId(), "a");
  uniform_b = glGetUniformLocation(mainShaderProg->programId(), "b");

  mainShaderProg->setUniformValue(uniform_a, -1.0f);
  mainShaderProg->setUniformValue(uniform_b, 1.0f);
}

void GLWidget::paintGL()
{
  qDebug() << "Paint";
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (renderer->coords->size() == 0)
    return;

  mainShaderProg->bind();
  glUniform1f(uniform_a, static_cast<float>(Expression::span.get_a()));
  glUniform1f(uniform_b, static_cast<float>(Expression::span.get_b()));
  mainShaderProg->release();

  renderRenderable(renderer.get(), mainShaderProg.get(), GL_LINE_STRIP);
}

void GLWidget::resizeGL(int w, int h)
{
  Q_UNUSED(w);
  Q_UNUSED(h);
}

void GLWidget::renderRenderable(Renderable *obj, QOpenGLShaderProgram *shaderProg, GLenum mode)
{
  obj->updateRenderable();
  glBindVertexArray(obj->vao);
  shaderProg->bind();
  glDrawArrays(mode, 0, obj->coords->size());
  glBindVertexArray(0);
  shaderProg->release();
}
