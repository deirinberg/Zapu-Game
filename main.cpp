#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //QPushButton *pb = new QPushButton("Timer");
    //QObject::connect(pb, SIGNAL(clicked()), &w, SLOT(switchTimer()));
    //pb->show();
    w.show();

    return a.exec();
}
