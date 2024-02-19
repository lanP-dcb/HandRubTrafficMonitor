#ifndef PROCESSCLASS_H
#define PROCESSCLASS_H

#include <QObject>
#include <mywidget.h>

class ProcessClass : public QObject
{
    Q_OBJECT
public:
    explicit ProcessClass(QObject *parent = nullptr);

signals:

private:
    MyWidget m_widget;
};

#endif // PROCESSCLASS_H
