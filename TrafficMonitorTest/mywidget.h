#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QObject>
#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

signals:

private:
    QWidget* m_parent;
};

#endif // MYWIDGET_H
