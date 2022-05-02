#include "gui.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui w;

    w.show();
    w.setInfo();
    return a.exec();
}
