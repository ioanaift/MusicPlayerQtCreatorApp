#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setStyle("fusion");
    MainWindow w;
    //w.setStyleSheet("background-image:url(:/images/buttons/grey.jpg)");
    w.show();

    return a.exec();
}
