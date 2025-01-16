#include "T2.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    T2 w;
    w.showMaximized();

    w.initializeCoordinateSystem();  // 初始化坐标系
    w.initializeTableView();  // 初始化表格视图

    return a.exec();
    
}
