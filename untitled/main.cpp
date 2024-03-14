#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QCoreApplication>
#include <QSurfaceFormat>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMenu>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // 创建 MainWindow 对象
    MainWindow mainWindow;


    QTranslator *qtTranslator = new QTranslator;
    //获取翻译文件路径并加载
    if(qtTranslator->load(QCoreApplication::applicationDirPath() + "/qt_zh_CN.qm")){
        a.installTranslator(qtTranslator);
    }
    else{
        qDebug("load failed!!\n");
        qDebug() << QCoreApplication::applicationDirPath();
    }


    // 图标 //
    // 创建QSystemTrayIcon
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(QIcon(":/Resource/main/icon.ico"), &a);
    // 创建菜单
    QMenu* trayMenu = new QMenu();
    QAction* showAction = new QAction("Show", &a);
    QAction* quitAction = new QAction("Quit", &a);

    // 添加动作到菜单
    trayMenu->addAction(showAction);
    trayMenu->addAction(quitAction);

    // 将菜单设置给QSystemTrayIcon
    trayIcon->setContextMenu(trayMenu);

    // 处理菜单动作的槽函数
    QObject::connect(showAction, &QAction::triggered, [&mainWindow]() {
        // 处理显示操作，你可以在这里实现窗口的显示逻辑
        mainWindow.show();
    });

    QObject::connect(quitAction, &QAction::triggered, &a, &QCoreApplication::quit);

    // 显示托盘图标
    trayIcon->show();
    // 图标 //


    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    QSurfaceFormat::setDefaultFormat(format);

    a.setStyle("fusion");

    // 显示主窗口
    mainWindow.show();

    return a.exec();
}
