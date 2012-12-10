#include "server_thread.h"
#define out qDebug()

server_thread::server_thread(QObject *parent, server_gui *serverInterface) : QThread(parent){
    this->serverInterface = serverInterface;

}

void server_thread::run(){

    out << "serverthread";

    //Server *meinServer = new Server("55313", this->serverInterface->getGameValues()[0], this->serverInterface->getGameValues()[1], this->serverInterface->getGameValues()[2]);

    int breite = 8, hoehe = 8, Spieler = 2;

    this->meinServer = new Server(breite, hoehe, Spieler);

    message = "none";
    this->exec();
}

void server_thread::NetServerStartGame(){
    this->meinServer->globalSend("400,");
}
