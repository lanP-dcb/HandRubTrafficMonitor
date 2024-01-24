#ifndef MAINMONITORWIN_H
#define MAINMONITORWIN_H

//#if UNIX
//#include <libappindicator/app-indicator.h>
//#undef signals
//#include <gtk/gtk.h>
//#endif
#include "common/configmanagement.h"
#include <QGuiApplication>
#include <QScreen>
#include <QObject>
#include <QWidget>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QMouseEvent>
#include <QEvent>

class MainMonitorWin : public QWidget
{
    Q_OBJECT
public:
    MainMonitorWin(QWidget *parent = nullptr);

public slots:
    void SlotMainWindowOperation(QObject* obj,bool checked,int value);

    void SlotSetWinOpacity(std::string key,int value);

private slots:
    void mousePressEvent(QMouseEvent *e) override;

    void mouseMoveEvent(QMouseEvent *e) override;

    void mouseReleaseEvent(QMouseEvent *e) override;

signals:

private:
    QDesktopWidget* desktop;
    bool mousePress{false};             // 左键点击
    QPoint m_pos;                       // 窗口移动
    bool pos_lock;                      // 窗口位置锁定
    bool mouseTransparent;              // 鼠标穿透
    bool cross;                         // 屏幕越界
};

#endif // MAINMONITORWIN_H
