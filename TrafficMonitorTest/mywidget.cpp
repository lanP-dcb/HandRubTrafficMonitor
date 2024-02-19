#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setGeometry(100,100,100,100);
    move(0,0);
}
