#include "trafficmonitor.h"
#include "ui_trafficmonitor.h"
#include <QDebug>

#define DEBUG(x) qDebug() <<__FUNCTION__<<__LINE__<<x

TrafficMonitor::TrafficMonitor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrafficMonitor)
{
    ui->setupUi(this);
//    setWindowFlag(Qt::WindowType::ToolTip);
    setGeometry(50,50,100,30);
    InitTray();
    Xml();
}

TrafficMonitor::~TrafficMonitor()
{    
    delete ui;
    if (nullptr != m_taskBarWidget) {
        delete m_taskBarWidget;
    }
}

void TrafficMonitor::InitTray()
{
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(":/icon/traffic.png"));
    m_trayIcon->show();
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

void TrafficMonitor::Xml()
{
    QFile file(":/Menuformat.xml");
    if (!file.open(QFileDevice::ReadOnly)) {
        DEBUG("文件打开失败！");
        return;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        DEBUG("操作的文件不是XML文件！");
        file.close();
        return;
    }
    QMenu *menu = new QMenu(this);
    QDomNodeList list = doc.documentElement().childNodes();
    InitMenu(list,menu);
    m_trayIcon->setContextMenu(menu);
    m_trayIcon->show();
    file.close();
}

void TrafficMonitor::InitMenu(const QDomNodeList &nodelist, QMenu *menu)
{
    for (int i = 0; i < nodelist.size(); i++) {
        QDomElement ele = nodelist.at(i).toElement();
        if (ele.nodeName() == "separator") {
            menu->addSeparator();
            continue;
        }
        QAction *action = new QAction();
        action->setObjectName(ele.attribute("obj"));
        action->setText(tr(ele.namedItem("name").firstChild().nodeValue().toUtf8()));
        action->setIcon(QIcon(ele.namedItem("icon").firstChild().nodeValue().toUtf8()));
        int type = ele.attribute("type").toInt();
        switch (type) {
        case 1:{
            action->setCheckable(true);
            action->setChecked(GetCfgValToBoolDef(G_SYSTEM, action->objectName().toUtf8().data(), QVariant(ele.attribute("def"))));
        }break;
        case 2:{
            QMenu *tmp = new QMenu();
            InitMenu(ele.namedItem("menu").toElement().childNodes(), tmp);
            action->setMenu(tmp);
        }break;
        case 3:{
            QActionGroup *group = new QActionGroup(this);
            group->setExclusive(true);
            InitMenu(ele.elementsByTagName("select"), group);
            QList<QAction*> list = group->actions();
            action->setActionGroup(group);
            group->setEnabled(true);
            menu->addActions(list);
        }break;
        default:break;
        }
        if (type != 3) {
            menu->addAction(action);
        }
    }
}

void TrafficMonitor::InitMenu(const QDomNodeList &nodelist, QActionGroup *group)
{
    for (int i = 0; i < nodelist.size(); i++) {
        QDomElement ele = nodelist.at(i).toElement();
        QAction *action = new QAction();
        action->setObjectName(ele.attribute("obj"));
        action->setText(tr(ele.namedItem("name").firstChild().nodeValue().toUtf8()));
        group->addAction(action);
    }
}

