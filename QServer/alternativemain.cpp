#include "alternativemain.h"



alternativeMAIN::alternativeMAIN()
{

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

    QObject::connect(meinSServer->uServer1,SIGNAL(setStone(int, int, int)),
                     meinSServer,SLOT(setStoneControl(int, int, int)));
    QObject::connect(meinSServer->uServer2,SIGNAL(setStone(int, int, int)),
                     meinSServer,SLOT(setStoneControl(int, int, int)));
    if(Spieler >= 3){
        QObject::connect(meinSServer->uServer3,SIGNAL(setStone(int, int, int)),
                     meinSServer,SLOT(setStoneControl(int, int, int)));
    }
    if(Spieler == 4){
        QObject::connect(meinSServer->uServer4,SIGNAL(setStone(int, int, int)),
                     meinSServer,SLOT(setStoneControl(int, int, int)));
    }

    //    connect(meinSServer, SIGNAL(setStone(int)), meinSServer,SLOT());

    while(1){
        //cout << "in while";
    }

}
