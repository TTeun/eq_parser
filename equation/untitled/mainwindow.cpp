#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "expression/evaluator.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->openGLWidget, SIGNAL( linear_span_changed(double, double) ), this, SLOT(linear_span_changed(double, double)));
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

void MainWindow::linear_span_changed(double a, double b)
{
  ui->a_spinbox->setValue(a);
  ui->b_spinbox->setValue(b);
  ui->openGLWidget->axes->set_ab(a, b);

  fill_and_update();
}

void MainWindow::fill_and_update()
{
  evaluator::fill_expr_1D(ui->openGLWidget->expression.get(), ui->openGLWidget->renderer.get());

  ui->openGLWidget->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
  qDebug() << QString::number(event->pos().x());
  qDebug() << QString::number(event->pos().y());
}
