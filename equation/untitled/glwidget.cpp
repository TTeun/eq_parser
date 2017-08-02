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

  uniform_a = glGetUniformLocation(mainShaderProg->programId(), "a");
  uniform_b = glGetUniformLocation(mainShaderProg->programId(), "b");

  mainShaderProg->setUniformValue(uniform_a, -1.0f);
  mainShaderProg->setUniformValue(uniform_b, 1.0f);
}

void GLWidget::paintGL()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  renderRenderable(axes->x_axis(), mainShaderProg.get(), GL_LINE_STRIP);
  renderRenderable(axes->y_axis(), mainShaderProg.get(), GL_LINE_STRIP);

  if (renderer->coords->size() == 0)
    return;

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
  Expression::span.incr_x(-dx);

  emit linear_span_changed(Expression::span.get_a(), Expression::span.get_b());

  auto& x_axis_coords = *(axes->x_axis()->coords.get());
  x_axis_coords[0] = QVector2D(Expression::span.get_a(), 0.0);
  x_axis_coords[1] = QVector2D(Expression::span.get_b(), 0.0);

  mainShaderProg->bind();
  glUniform1f(uniform_a, static_cast<float>(Expression::span.get_a()));
  glUniform1f(uniform_b, static_cast<float>(Expression::span.get_b()));
  mainShaderProg->release();

}
