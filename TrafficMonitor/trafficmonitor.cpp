#include "trafficmonitor.h"

TrafficMonitor::TrafficMonitor()
{
    m_mainWin = new MainMonitorWin();
    m_trayMngmt = new TrayManagement();
    if (!m_trayMngmt->InitUi()) {
        DEBUG("初始化托盘程序失败");
        exit(-1);
    }
    InitConnect();
    m_trayMngmt->InitCfg();
}

TrafficMonitor::~TrafficMonitor()
{    
    if (nullptr != m_taskBarWidget) {
        delete m_taskBarWidget;
    }
    if (nullptr != m_trayMngmt) {
        delete m_trayMngmt;
    }
    if (nullptr != m_mainWin) {
        delete m_mainWin;
    }
}

void TrafficMonitor::InitConnect()
{
    connect(m_trayMngmt, &TrayManagement::SignalMainWindowOperation,
            m_mainWin, &MainMonitorWin::SlotMainWindowOperation);
    connect(m_trayMngmt, &TrayManagement::SignalSetWinOpacity,
            m_mainWin, &MainMonitorWin::SlotSetWinOpacity);
}

