#include "hostsblocker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HostsBlocker w;
    w.show();
    return a.exec();
}
