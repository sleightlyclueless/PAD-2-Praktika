#include "mainwindow.h"

#include <QApplication>
#include <ctime>


int main(int argc, char *argv[])
{
    srand(time(nullptr));

    QApplication a(argc, argv);
    Mainwindow w;
    w.show();

    return a.exec();
}
