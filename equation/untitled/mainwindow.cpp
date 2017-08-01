#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "expression/evaluator.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
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



void MainWindow::on_a_spinbox_valueChanged(double arg1)
{
  Expression::span.set_a(arg1);
  fill_and_update();
}

void MainWindow::on_b_spinbox_valueChanged(double arg1)
{
  Expression::span.set_b(arg1);
  fill_and_update();
}

void MainWindow::on_n_spinbox_valueChanged(int arg1)
{
  Expression::span.set_n(arg1);
  fill_and_update();
}

void MainWindow::fill_and_update()
{
  evaluator::fill_expr_1D(ui->openGLWidget->expression.get(), ui->openGLWidget->renderer.get());

  ui->openGLWidget->update();
}
