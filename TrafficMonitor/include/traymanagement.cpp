#include "traymanagement.h"

TrayManagement::TrayManagement()
{
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(":/icon/notifyicon.ico"));
    m_trayMenu = new QMenu();
}

TrayManagement::~TrayManagement()
{
    delete m_trayMenu;
    delete m_trayIcon;
}

bool TrayManagement::InitUi()
{
    QFile file(":/Menuformat.xml");
    if (!file.open(QFileDevice::ReadOnly)) {
        DEBUG("文件打开失败！");
        return false;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        DEBUG("操作的文件不是XML文件！");
        return false;
    }
    m_init_action.clear();
    m_obj_map.clear();
    InitMenu(doc.documentElement().childNodes(), m_trayMenu);
    m_trayIcon->setContextMenu(m_trayMenu);
    m_trayIcon->show();
    file.close();
    return true;

    // connect(m_trayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason){
    //     switch (reason) {
    //     case QSystemTrayIcon::Unknown:break;
    //     case QSystemTrayIcon::Context:break;
    //     case QSystemTrayIcon::DoubleClick:break;
    //     case QSystemTrayIcon::Trigger:break;
    //     case QSystemTrayIcon::MiddleClick:break;
    //     default:break;
    //     }
    // });
    //任务栏显示的内容
    //    {
    //        m_taskBarWidget = new QWidget;
    //        m_taskBarWidget->setWindowTitle("TaskBarWidget");
    //        m_taskBarWidget->setToolTip("TaskBarWidgetTaskBarWidgetTaskBarWidgetTaskBarWidget");
    //        m_taskBarWidget->setStyleSheet("background-color: rgb(115, 210, 22);");
    //        m_taskBarWidget->resize(100,20);
    //        m_taskBarWidget->show();
    //        WId idTaskBar = m_taskBarWidget->winId();
    //        for (QScreen *screen: QGuiApplication::screens()) {
    //            QWindow *window;
    //        }
    //    }
}

bool TrayManagement::InitCfg()
{
    while(!m_init_action.isEmpty()) {
        emit m_init_action.first()->triggered(m_init_action.first()->isChecked());
        m_init_action.removeFirst();
    }
    return true;
}

QMenu *TrayManagement::GetMenu()
{
    return m_trayMenu;
}

void TrayManagement::InitMenu(const QDomNodeList &nodelist, QMenu *menu)
{
    for (int i = 0; i < nodelist.size(); i++) {
        QDomElement ele = nodelist.at(i).toElement();
        if (ele.nodeName() == "separator") {
            menu->addSeparator();
            continue;
        }
        QAction *action = new QAction(this);
        action->setObjectName(ele.attribute("obj"));
        action->setText(tr(ele.namedItem("name").firstChild().nodeValue().toUtf8()));
        action->setIcon(QIcon(ele.namedItem("icon").firstChild().nodeValue().toUtf8()));
        int type = ele.attribute("type").toInt();
        switch (type) {
        case 1:{
            action->setCheckable(true);
            action->setChecked(GetCfgValToBoolDef(G_SYSTEM, action->objectName().toUtf8().data(), QVariant(ele.attribute("def"))));
            m_init_action.append(action);
        }break;
        case 2:{
            QMenu *tmp = new QMenu();
            InitMenu(ele.namedItem("menu").toElement().childNodes(), tmp);
            action->setMenu(tmp);
        }break;
        case 3:{
            QActionGroup *group = new QActionGroup(this);
            group->setExclusive(true);
            InitGroup(ele.elementsByTagName("select"), group);
            QList<QAction*> list = group->actions();
            action->setActionGroup(group);
            group->setEnabled(true);
            menu->addActions(list);
            int def = ele.attribute("def").toInt();
            int cur = GetCfgVal(G_SYSTEM,ele.namedItem("cfg").firstChild().nodeValue().toUtf8().data()).toInt();
            if (cur > def) {
                m_init_action.append(group->actions().at(cur));
                group->actions().at(cur)->setChecked(true);
            } else {
                m_init_action.append(group->actions().at(def));
                group->actions().at(def)->setChecked(true);
            }
        }break;
        default:break;
        }
        if (type != 3) {
            menu->addAction(action);
            m_obj_map.insert(action->objectName(),ele.namedItem("value").firstChild().nodeValue().toInt());
            connect(action, &QAction::triggered, this, &TrayManagement::QActionEmitForwardSlots);
        }
    }
}

void TrayManagement::InitGroup(const QDomNodeList &nodelist, QActionGroup *group)
{
    for (int i = 0; i < nodelist.size(); i++) {
        QDomElement ele = nodelist.at(i).toElement();
        QAction *action = new QAction();
        action->setObjectName(ele.attribute("obj"));
        action->setText(tr(ele.namedItem("name").firstChild().nodeValue().toUtf8()));
        action->setCheckable(true);
        group->addAction(action);
        m_obj_map.insert(action->objectName(),ele.namedItem("value").firstChild().nodeValue().toInt());
        connect(action, &QAction::triggered, this, &TrayManagement::QActionEmitForwardSlots);
    }
}

void TrayManagement::QActionEmitForwardSlots(bool checked)
{
    obj_name = sender()->objectName();
    int value = m_obj_map.find(obj_name).value();
//    DEBUG(obj_name << checked << value);
    switch (value) {
    case 1:break;
    case 2: case 3: case 4: case 5: case 6: case 7:case 14:
        emit SignalMainWindowOperation(sender(),checked,value);break;
    case 8: case 9: case 10: case 11:
        emit SignalSetWinOpacity("group_win_alpha",value);break;
    case 12:break;
    case 13:break;
    case 15:break;
    case 16:break;
    case 17:break;
    case 18:break;
    case 19:break;
    case 20:break;
    case 21:break;
    case 22:break;
    case 23:QApplication::quit(); break;
    case 24:break;
    case 25:break;
    case 26:break;
    }
}

/*
 * 其他   右键菜单
1.连接详情
    2.总是置顶
    3.鼠标穿透
    4.锁定窗口位置
    5.显示更多信息
6.显示任务栏窗口
    7.显示主窗口
    8.窗口不透明度-100
    9.窗口不透明度-80
    10.窗口不透明度-60
    11.窗口不透明度-40
12.更换皮肤
13.更换通知区图标
    14.允许超出屏幕边界(单屏幕)
15.历史流量统计
16.插件管理
17.选项
18.帮助
19.常见问题
20.更新日志
21.关于
22.检查更新
    23.退出
24.刷新网络链接列表
25.自动选择
26.选择全部
*/
