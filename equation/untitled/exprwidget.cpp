#include "exprwidget.h"
#include <QDebug>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>

ExprWidget::ExprWidget(QWidget *parent) : QWidget(parent)
{
  QLayout *l = new QHBoxLayout;
  l->setContentsMargins(0, 0, 0, 0);
  this->setLayout(l);
  QLineEdit *expr_line = new QLineEdit();
  this->layout()->addWidget(expr_line);

  add_btn = new QPushButton("+");
  add_btn->setMaximumSize(25, 25);
  this->layout()->addWidget(add_btn);

  sub_btn = new QPushButton("-");
  sub_btn->setMaximumSize(25, 25);
  this->layout()->addWidget(sub_btn);

}
