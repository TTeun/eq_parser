#include "mainwindow.h"
#include "ui_mainwindow.h"

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
  ui->openGLWidget->expression.parse_equation(ui->equation->text());
  if (ui->openGLWidget->expression.expr.arguments.size() == 1)
    qDebug() << ui->openGLWidget->expression.eval_at(ui->openGLWidget->expression.expr.arguments[0], 2);

  ui->openGLWidget->paintGL();
}
