#include "T2.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    T2 w;
    w.showMaximized();

    w.initializeCoordinateSystem();  // ��ʼ������ϵ
    w.initializeTableView();  // ��ʼ�������ͼ

    return a.exec();
    
}
