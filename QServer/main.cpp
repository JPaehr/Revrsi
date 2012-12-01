#include <QCoreApplication>
#include "socket.h"
#include <iostream>
#include "server.h"
#include <vector>

int main(){

    Server meinServer("55313", 10, 10);



    //Server meinServer("55313");
    //recv in Thread
    meinServer.start();

    //Server meinServer2("55314");
    //meinServer2.start();

    //senden

    //meinServer.ausfuehren(meinServer.StringSpielstand());
    meinServer.ausfuehren("100,2,2,");
    cout << "bis hier gehts"<< endl;


    meinServer.ausfuehren("500,5,5,6,6,");
    cout << "sdcsdcsdcsdcsdcsdcd"<< endl;
    while(1){
    }
    return 0;
}
