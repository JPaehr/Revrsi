#include "server_thread.h"
#define out qDebug()

server_thread::server_thread(QObject *parent, server_gui *serverInterface) : QThread(parent){
    this->serverInterface = serverInterface;

}

void server_thread::run(){
    out << "serverthread";

    Server *meinServer = new Server("55313", this->serverInterface->getGameValues()[0], this->serverInterface->getGameValues()[1], this->serverInterface->getGameValues()[2]);
    message = "none";

    //Server meinServer("55313");
    //recv in Thread
    meinServer->start();

    //Server meinServer2("55314");
    //meinServer2.start();

    //senden

    //meinServer.senden(meinServer.StringSpielstand());
    meinServer->senden("100,3,3,");
    //cout << "bis hier gehts"<< endl;


    meinServer->senden("500,5,5,4,4,3,4,6,6,5,");
    std::string s;
    while(1){
        while(message != QString("none")){
            meinServer->senden(message.toStdString());
            out << "message While schleife";
        }
        sleep(1);
        out << "std while loop";
    }
}
