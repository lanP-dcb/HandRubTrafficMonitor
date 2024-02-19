#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this,[&](){
//        QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
//        foreach (const QNetworkInterface &interface, interfaces) {
//            // 输出网络接口信息
//            qDebug() << "Interface Name:" << interface.name();
//            qDebug() << "Interface Description:" << interface.humanReadableName();
//            qDebug() << interface.hardwareAddress() << interface.humanReadableName()
//                     << interface.allAddresses()
//                     << interface.allInterfaces()
//                     ;
//            // 获取接口的网络统计信息
//            QNetworkDatagram datagram;
////            datagram.setInterfaceIndex(interface.index());
//            qDebug() << "------------------------";
//        }
    });
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

