#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "server.h"

#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
  /*  std::ifstream file("C:/Users/1/networks/server_network/test.txt");
   // std::cout << file.is_open();
    std::string ln;
    std::string src;
    while (std::getline(file, ln)) { src += ln; src += '\n'; }

    Problem *p = new Problem(src, 0);
  //  for (auto &i : p->tasks) {std::cout << i.first << ' '; for (auto j : i.second.prev) std::cout << j->getName() << ' ' ; std::cout << " !! "; for (auto j : i.second.next) std::cout << j->getName() << ' '; std::cout << '\n';}
   // std::cout << p->tasks["2"].getDuration() << '\n';
 //   for (auto &i : p->tasks["2"].assignments) std::cout << i.resource->name << ' ' << i.task->getName() << '\n';
    MixedSolver s1(p, NULL, 3);
    s1.solve();
    std::cout << s1.solution.second << '\n';*/


    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoserver");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1234"));
    parser.addOption(portOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();

    EchoServer *server = new EchoServer(port, debug);
    QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
