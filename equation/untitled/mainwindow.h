#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "exprwidget.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public slots:
    void axes_changed(double x_min, double x_max, double y_min, double y_max);
    void add_expr_widget();

  private slots:
    void on_equation_editingFinished();
    void on_pushButton_clicked();

  private:
    void fill_and_update();
    size_t expr_widget_count = 1;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
