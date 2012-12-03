#include "server_thread.h"


server_thread::server_thread(QObject *parent) : QThread(parent){
}

void server_thread::run(){
    Server *meinServer = new Server("55313", 10, 10);

    message = "none";

    //Server meinServer("55313");
    //recv in Thread
    meinServer->start();

    //Server meinServer2("55314");
    //meinServer2.start();

    //senden

    //meinServer.ausfuehren(meinServer.StringSpielstand());
    meinServer->ausfuehren("100,3,3,");
    cout << "bis hier gehts"<< endl;


    meinServer->ausfuehren("500,5,5,4,4,3,4,6,6,5,");
    std::string s;
    while(1){
        while(message != QString("none")){
            meinServer->ausfuehren(message.toStdString());
        }
    }
}
