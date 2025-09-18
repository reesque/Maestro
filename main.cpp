#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");
    MainWindow w;
    w.setFixedSize(800, 600);
    w.setWindowTitle("Maestro");
    w.show();
    return a.exec();
}
