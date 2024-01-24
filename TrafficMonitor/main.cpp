#include "trafficmonitor.h"
#include <QApplication>

//#define GTK_ICON "/home/dcb/mnt/code/log/accumulate/HandRubTrafficMonitor/TrafficMonitor/icon/test.ico"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrafficMonitor m_trafficMonitor;
    return a.exec();


//    AppIndicator *indicator      = NULL;
//    GtkMenuShell *indicator_menu = NULL;
//    // 1. 初始化GTK
//    if (gtk_init_check(0, NULL) == FALSE) {
//        return -1;
//    }
//    //  2. app-indicator 创建应用程序状态栏的图标
//    //  注意：图标文件名必须是绝对路径否则会出现无法显示问题。
//    indicator = app_indicator_new("my-indicator",
//                                  GTK_ICON,
//                                  APP_INDICATOR_CATEGORY_OTHER);
//    app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
//    // 设置图标
////    app_indicator_set_icon(indicator, GTK_ICON);
//    // 3. 初始化菜单项
////    indicator_menu = create_menu();
//    // 4. 关联到状态栏
//    app_indicator_set_menu(indicator, GTK_MENU (indicator_menu));
////    app_indicator_set_menu(indicator, nullptr);
//    // 5. 启动GTK程序，并阻塞进程。
//    app_indicator_set_label(indicator,std::string("label_data").c_str(),"test");

//    gtk_main();
}

//void hello_cb(GtkMenuItem *item, gpointer data) {
////    gtk_widget_hide();
////    gtk_main_level();
//}

//GtkMenuShell *create_menu() {
//    GtkWidget    *hello_item;
//    GtkWidget    *quit_item;
//    GtkMenuShell *indicator_menu;

//    indicator_menu = (GtkMenuShell *) gtk_menu_new();

//    hello_item = gtk_check_menu_item_new_with_label("你好！");
//    // 菜单项定义
//    // gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(hello_item), FALSE);
//    // 表示可交互
//    // gtk_widget_set_sensitive(hello_item, TRUE);
//    // 设置点击事件回调函数
//    g_signal_connect(hello_item, "activate", G_CALLBACK(hello_cb), NULL);


//    quit_item = gtk_check_menu_item_new_with_label("退出");
//    // gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(quit_item), FALSE);
//    // gtk_widget_set_sensitive(quit_item, TRUE);
//    g_signal_connect(quit_item, "activate", G_CALLBACK(gtk_main_quit), NULL);

//    // 显示菜单项目，并添加到菜单中。
//    gtk_widget_show(hello_item);
//    gtk_widget_show(quit_item);
//    gtk_menu_shell_append(indicator_menu, hello_item);
//    gtk_menu_shell_append(indicator_menu, quit_item);

//    return indicator_menu;
//}
