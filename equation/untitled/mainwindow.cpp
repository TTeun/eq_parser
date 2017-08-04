#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "expression/evaluator.h"
#include <QMouseEvent>
#include <QLayout>
#include "exprwidget.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->openGLWidget, SIGNAL( linear_span_changed(double, double, double, double) ), this, SLOT(axes_changed(double, double, double, double)));
  connect(this, SIGNAL(fill_and_update()), SLOT(update_status_bar()));
  ui->statusBar->showMessage("Empty");

  QLayout *l = new QVBoxLayout;
  ui->widget->setLayout(l);
  add_expr_widget();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_equation_editingFinished()
{
  ui->openGLWidget->expression->parse_equation(ui->equation->text());
  fill_and_update();
}

void MainWindow::axes_changed(double x_min, double x_max, double y_min, double y_max)
{
  ui->openGLWidget->axes->set_domain(x_min, x_max);
  ui->openGLWidget->axes->set_range(y_min, y_max);
  fill_and_update();
}

void MainWindow::add_expr_widget()
{
  ExprWidget *e = new ExprWidget;
  e->resize(ui->widget->width(), 35);
  ui->widget->layout()->addWidget(e);
  connect(e->add_btn, SIGNAL(pressed()), this, SLOT(add_expr_widget()));

  ++expr_widget_count;
  ui->widget->resize(ui->widget->width(), 32 * expr_widget_count);
}

void MainWindow::fill_and_update()
{
  evaluator::fill_expr_1D(ui->openGLWidget->expression.get(), ui->openGLWidget->renderer.get());

  auto state = ui->openGLWidget->expression->get_state();
  ui->statusBar->showMessage(
    state == Expression::EXPR_STATE::OK    ? "OK" :
    state == Expression::EXPR_STATE::EMPTY ? "Empty" :
    state == Expression::EXPR_STATE::ERROR ? "Parse error" :
    " "
  );
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_clicked()
{

}
