#include "glwidget.h"
#include <QMouseEvent>

GLWidget::GLWidget(QWidget *parent)
  :
  QOpenGLWidget(parent),
  renderer(make_unique<Renderable>(this)),
  expression(make_unique<Expression>()),
  axes(make_unique<Axes>(this)),
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
  axes->registerAxes();
  createShaderPrograms();
}

void GLWidget::createShaderPrograms()
{
  mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
  mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");
  mainShaderProg->link();

  uniform_x_min = glGetUniformLocation(mainShaderProg->programId(), "x_min");
  uniform_x_max = glGetUniformLocation(mainShaderProg->programId(), "x_max");
  uniform_y_min = glGetUniformLocation(mainShaderProg->programId(), "y_min");
  uniform_y_max = glGetUniformLocation(mainShaderProg->programId(), "y_max");

  mainShaderProg->setUniformValue(uniform_x_min, -1.0f);
  mainShaderProg->setUniformValue(uniform_x_max, 1.0f);
  mainShaderProg->setUniformValue(uniform_y_min, -1.0f);
  mainShaderProg->setUniformValue(uniform_y_max, 1.0f);

}

void GLWidget::paintGL()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (renderer->coords->size() != 0)
    renderRenderable(renderer.get(), mainShaderProg.get(), GL_LINE_STRIP);

  renderRenderable(axes->x_axis(), mainShaderProg.get(), GL_LINE_STRIP);
  renderRenderable(axes->y_axis(), mainShaderProg.get(), GL_LINE_STRIP);
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

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
  double x = 2.0 * event->pos().x() / this->width() - 1;
  double y = -2.0 * event->pos().y() / this->width() + 1;

  update_linear_span(x - x_click, y - y_click);
  x_click = x;
  y_click = y;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    x_click = 2.0 * event->pos().x() / this->width() - 1;
    y_click = -2.0 * event->pos().y() / this->width() + 1;
  }
}

void GLWidget::update_linear_span(double dx, double dy)
{
  Axes::domain.incr(-dx);
  Axes::range.incr(-dy);

  emit linear_span_changed(
    Axes::domain.min(),
    Axes::domain.max(),

    Axes::range.min(),
    Axes::range.max()
  );

  mainShaderProg->bind();
  glUniform1f(uniform_x_min, Axes::domain.min());
  glUniform1f(uniform_x_max, Axes::domain.max());
  glUniform1f(uniform_y_min, Axes::range.min());
  glUniform1f(uniform_y_max, Axes::range.max());
  mainShaderProg->release();
}
