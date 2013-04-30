#include <QtGui/QApplication>
#include "mainwindow.h"

/** Main function sets applications to blank commandline arguments,
 *  creates a new window and shows it.
 *
 *  @return a.exec()
 */
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
