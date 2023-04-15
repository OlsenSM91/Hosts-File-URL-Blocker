#include "hostblocker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HostBlocker w;
    w.show();
    return a.exec();
}
