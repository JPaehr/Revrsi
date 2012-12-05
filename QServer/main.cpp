#include <QCoreApplication>
//#include <QApplication>
#include "socket.h"
#include <iostream>
#include "server.h"
#include <vector>
#include <string>
#include "superserver.h"

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    int breite = 8, hoehe = 8, Spieler = 3;

    SuperServer *meinSServer=new SuperServer(breite, hoehe, Spieler);

    cout << "pre exec";
    return a.exec();
}
