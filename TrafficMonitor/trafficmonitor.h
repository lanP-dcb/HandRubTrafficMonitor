#ifndef TRAFFICMONITOR_H
#define TRAFFICMONITOR_H



#include "common/configmanagement.h"
#include "include/mainmonitorwin.h"
#include "include/traymanagement.h"
#include <QObject>


class TrafficMonitor : public QObject
{
    Q_OBJECT
public:
    TrafficMonitor();
    ~TrafficMonitor();

    void InitConnect();

private:
    MainMonitorWin *m_mainWin{};        // 主窗口
    TrayManagement *m_trayMngmt{};      // 系统托盘窗口
    QWidget *m_taskBarWidget{};         // 任务栏窗口

#if UNIX
//    AppIndicator *indicator;
#endif

};
#endif // TRAFFICMONITOR_H
