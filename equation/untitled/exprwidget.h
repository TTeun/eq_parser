#ifndef EXPRWIDGET_H
#define EXPRWIDGET_H

#include <QWidget>
#include <QPushButton>

class ExprWidget : public QWidget {
    Q_OBJECT
  public:
    explicit ExprWidget(QWidget *parent = nullptr);

    QPushButton *add_btn;
    QPushButton *sub_btn;

  signals:

  public slots:

  private:
};

#endif // EXPRWIDGET_H
