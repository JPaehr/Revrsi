#include <QCoreApplication>
#include "socket.h"
#include <iostream>
#include "server.h"
#include <vector>
#include <string>
#include "superserver.h"

int main(){

    /*
    Server meinServer("55313", 10, 10, 3);



    //Server meinServer("55313");
    //recv in Thread
    meinServer.start();

    //Server meinServer2("55314");
    //meinServer2.start();

    //senden

    //meinServer.ausfuehren(meinServer.StringSpielstand());
    meinServer.senden("100,10,10,");



    //meinServer.senden("500,5,5,4,4,3,4,6,6,5,");

    meinServer.senden(meinServer.StringSpielstand());

    std::string s;
    while(1){
       cin >> s;
       meinServer.senden(s);
    }
    */
    int breite = 8, hoehe = 8, Spieler = 2;

    SuperServer *meinSServer=new SuperServer(breite, hoehe, Spieler);



    //    connect(meinSServer, SIGNAL(setStone(int)), meinSServer,SLOT());

    while(1){
        //cout << "in while";
    }

    return 0;
}
