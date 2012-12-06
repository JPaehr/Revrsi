#include "server_thread.h"
#define out qDebug()

server_thread::server_thread(QObject *parent, server_gui *serverInterface) : QThread(parent){
    this->serverInterface = serverInterface;

}

void server_thread::run(){
    out << "serverthread";

    //Server *meinServer = new Server("55313", this->serverInterface->getGameValues()[0], this->serverInterface->getGameValues()[1], this->serverInterface->getGameValues()[2]);

    int breite = 8, hoehe = 8, Spieler = 3;

    SuperServer *meinSServer=new SuperServer(breite, hoehe, Spieler);

    message = "none";



}
