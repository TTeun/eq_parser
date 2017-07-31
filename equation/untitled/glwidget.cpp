#include "glwidget.h"
#include "parser/print.h"
#include "parser/simplify.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void GLWidget::resizeGL(int w, int h)
{
  Q_UNUSED(w);
  Q_UNUSED(h);
}

void GLWidget::parse_equation(QString const &str)
{

  std::string eq = str.toUtf8().constData();

  std::string::const_iterator iter = eq.begin();
  std::string::const_iterator end = eq.end();

  expr = client::expression();
  bool r = phrase_parse(iter, end, exp_parser{} >> qi::eoi, space, expr);
  if (r) {
    client::collapsed_type c = boost::apply_visitor(client::collapse_visitor(), expr.syntax_tree.type);
    if (c.can_collapse)
      expr.syntax_tree.type = c.value;

    client::print_tree(expr);
  } else
    qDebug() << "Error in parse";

}
