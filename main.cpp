#include "mainwindow.h"
#include <QApplication>
#include <mimalloc-new-delete.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
