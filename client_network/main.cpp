#include <QtGui>
#include <QApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCPClient c;
    c.show();

    return a.exec();
}
