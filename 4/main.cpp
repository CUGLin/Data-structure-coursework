#include "CampusNavigation.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CampusNavigation w;
    w.showMaximized();
    return a.exec();
}