#ifndef TRAFFICMONITOR_H
#define TRAFFICMONITOR_H

#include "common/configmanagement.h"
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QScreen>
#include <QWindow>
#include <QDomDocument>
#include <QActionGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class TrafficMonitor; }
QT_END_NAMESPACE

class TrafficMonitor : public QMainWindow
{
    Q_OBJECT

public:
    TrafficMonitor(QWidget *parent = nullptr);
    ~TrafficMonitor();

private:
    void InitTray();
    void Xml();
    void InitMenu(const QDomNodeList& nodelist, QMenu* menu);
    void InitMenu(const QDomNodeList& nodelist, QActionGroup* group);
    Ui::TrafficMonitor *ui;
    QSystemTrayIcon *m_trayIcon{};      // 系统托盘
    QMenu  *m_trayMenu{};               // 托盘菜单

    QList<QAction*> m_trayActionList;   // 托盘菜单右键列表
    QWidget *m_taskBarWidget{};         // 任务栏窗口
//    QAction *


};
#endif // TRAFFICMONITOR_H
