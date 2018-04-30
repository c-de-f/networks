#include <QtGui>
#include <QApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCPServer s;
    s.show();

    return a.exec();
}
