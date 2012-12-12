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
    QApplication::processEvents();

    this->meinServer->uServer1->start();
    while(!this->meinServer->uServer1->connected ){
        QApplication::processEvents();
    }

    this->meinServer->uServer2->start();
    while(!this->meinServer->uServer2->connected){
        QApplication::processEvents();
    }

    if(Spieler > 2){
        while(!this->meinServer->uServer3->connected){
            QApplication::processEvents();
        }
    }
    if(Spieler >= 4){
        while(!this->meinServer->uServer4->connected){
            QApplication::processEvents();
        }
    }
    this->exec();
}

void server_thread::NetServerStartGame(){
    this->meinServer->globalSend("400,");
}
