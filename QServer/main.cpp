#include <QCoreApplication>
//#include <QApplication>
#include "socket.h"
#include <iostream>
#include "subServer.h"
#include <vector>
#include <string>
#include "server.h"

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    int breite = 8, hoehe = 8, Spieler = 3;

    Server *meinSServer=new Server(breite, hoehe, Spieler);

    cout << "pre exec";
    return a.exec();
}
