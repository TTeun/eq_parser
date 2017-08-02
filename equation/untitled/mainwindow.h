#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public slots:
    void linear_span_changed(double a, double b);

  private slots:
    void on_equation_editingFinished();

  protected:
    void mouseMoveEvent(QMouseEvent *event);

  private:
    Ui::MainWindow *ui;

    void fill_and_update();
};

#endif // MAINWINDOW_H
