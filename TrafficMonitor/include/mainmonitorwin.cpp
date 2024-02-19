#include "mainmonitorwin.h"



MainMonitorWin::MainMonitorWin(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(50,50,100,100);
    // 鼠标是否穿透
    setAttribute(Qt::WA_TransparentForMouseEvents,
                 GetCfgValToBool(G_SYSTEM,"menu_set_mouse_penetration"));
    // 无边框
    setWindowFlags(Qt::FramelessWindowHint);
    // 窗口位置
    desktop = QApplication::desktop();
    QApplication::screens();
    if (GetCfgVal(G_SYSTEM,WIN_POS_X).isNull()) {
        SetCfgVal(G_SYSTEM,WIN_POS_X,desktop->width()-this->width());
        SetCfgVal(G_SYSTEM,WIN_POS_Y,desktop->height()-this->height());
    }
    move(GetCfgVal(G_SYSTEM,WIN_POS_X).toInt(), GetCfgVal(G_SYSTEM,WIN_POS_Y).toInt());

    //主窗口任务栏
    QScreen *primaryScreen =QGuiApplication::primaryScreen();
    QRect availableGeometry = primaryScreen->availableGeometry();
    DEBUG(availableGeometry.width());
}

void MainMonitorWin::SetMenu(QMenu *menu)
{
    m_menu = menu;
}

void MainMonitorWin::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        if (pos_lock)
            return;
        mousePress = true;
        m_pos = e->pos();
    } else if (e->button() == Qt::RightButton) {
        m_menu->exec(e->globalPos());
    }
}

void MainMonitorWin::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePress) {
        move(e->pos()- m_pos + this->pos());
    }
}

void MainMonitorWin::mouseReleaseEvent(QMouseEvent *e)
{
    (void)e;
    if (mousePress) {
        mousePress = false;
        if (!cross) {
            static int l_x = QGuiApplication::primaryScreen()->availableGeometry().x();
            static int l_y = QGuiApplication::primaryScreen()->availableGeometry().y();
            static int h_x = QGuiApplication::primaryScreen()->availableGeometry().width() - width();
            static int h_y = QGuiApplication::primaryScreen()->availableGeometry().height() - height();
            if (pos().x() < l_x)
                move(l_x, pos().y());
            if (pos().x() > h_x)
                move(h_x, pos().y());
            if (pos().y() < l_y)
                move(pos().x(),l_y);
            if (pos().y() > h_y)
                move(pos().x(), h_y);
        }
        SetCfgVal(G_SYSTEM,WIN_POS_X,pos().x());
        SetCfgVal(G_SYSTEM,WIN_POS_Y,pos().y());
    }
}

void MainMonitorWin::SlotMainWindowOperation(QObject *obj, bool checked, int value)
{
    SetCfgVal(G_SYSTEM,obj->objectName().toUtf8().data(),checked);
    switch (value) {
    case 2: { // 置顶窗口
        checked ? setWindowFlag(Qt::ToolTip, true)
                : setWindowFlag(Qt::ToolTip, false);
        show();
    }break;
    case 3:{ // 鼠标穿透
        static bool first_init = true;
        if (first_init) {
            first_init = false;
            break;
        }
        QMessageBox::information(nullptr,tr("信息"),tr("该设置重启应用后生效"));
        // checked ? mouseTransparent = true : mouseTransparent = false;
    }break;
    case 4:{ // 锁定窗口位置
        checked ? pos_lock = true : pos_lock = false;
    }break;
    case 7:{ // 显示主窗口
        checked ? show() : hide();
    }break;
    case 14:{ // 超出屏幕边界
        checked ? cross = true : cross = false;
    }
    default:break;
    }
}

void MainMonitorWin::SlotSetWinOpacity(std::string key, int value)
{
    switch (value) {
    case 8:setWindowOpacity(1.0);break;
    case 9:setWindowOpacity(0.8);break;
    case 10:setWindowOpacity(0.6);break;
    case 11:setWindowOpacity(0.4);break;
    default:break;
    }
    SetCfgVal(G_SYSTEM,key,value - 8);
}
