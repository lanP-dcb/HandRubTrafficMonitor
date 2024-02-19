#ifndef NETWORKMONITOR_H
#define NETWORKMONITOR_H

#include <QThread>

class NetworkMonitor : public QThread
{
    Q_OBJECT
public:
    NetworkMonitor();

    ~NetworkMonitor();

private:

};

#endif // NETWORKMONITOR_H
