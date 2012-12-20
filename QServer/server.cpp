#include "server.h"
#include "subServer.h"
//#include "Logic.h"
//#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Server::Server(int breite, int hoehe, int Spieler){

    this->uServer1 = new subServer(this,"55313", breite, hoehe, Spieler, 1);
    this->uServer2 = new subServer(this,"55314", breite, hoehe, Spieler, 2);
    if(Spieler >= 3){
        this->uServer3 = new subServer(this,"55315", breite, hoehe, Spieler, 3);
    }
    if(Spieler == 4){
        this->uServer4 = new subServer(this,"55316", breite, hoehe, Spieler, 4);
    }
    QObject::connect(this->uServer1,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
    QObject::connect(this->uServer1,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
    QObject::connect(this->uServer1,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
    QObject::connect(this->uServer1,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));

    QObject::connect(this->uServer2,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
    QObject::connect(this->uServer2,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
    QObject::connect(this->uServer2,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
    QObject::connect(this->uServer2,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));



    if(Spieler >= 3){
        QObject::connect(this->uServer3,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
        QObject::connect(this->uServer3,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
        QObject::connect(this->uServer3,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
        QObject::connect(this->uServer3,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));

    }
    if(Spieler == 4){
        QObject::connect(this->uServer4,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
        QObject::connect(this->uServer4,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
        QObject::connect(this->uServer4,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
        QObject::connect(this->uServer4,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));

    }
    this->uServer1Connected = false;
    this->uServer2Connected = false;
    this->uServer3Connected = false;
    this->uServer4Connected = false;

    stringstream String100;
    String100 << "100,";
    String100 << breite;
    String100 << ",";
    String100 << hoehe;
    String100 << ",";
    String100 << Spieler;
    String100 << ",";
    cout << String100.str() << endl;


    this->logic = new Logic(breite, hoehe, Spieler);
    this->logic->setInitStones();
    this->fields = this->logic->getFields();

    this->width = breite;
    this->heigth = hoehe;
    this->players = Spieler;

    //this->uServer1->initServer();
    //this->uServer1->start();
    //this->uServer1->senden("800,1,"); //Neue Client ID
    //this->uServer1->senden("999,1,"); //Akt Player
    //this->uServer1->id = 1;
    //this->uServer1->senden(String100.str()); //Code 100 FeldDaten breite höhe spielernum
    //this->uServer1->senden(StringSpielstand()); //Code 500 FeldVektor senden
    //QApplication::processEvents();

    //this->uServer2->initServer();
    //this->uServer2->start();
    //this->uServer2->senden("800,2,"); //Neue Client ID
    //this->uServer2->senden("999,1,"); //Akt Player
    //this->uServer2->senden(String100.str()); //Code 100
    //this->uServer2->senden(StringSpielstand()); //Code 500

    if(Spieler >= 3){
        this->uServer3->initServer();
        //this->uServer3 = new Server("55315", breite, hoehe, Spieler, this);
        this->uServer3->start();
        this->uServer3->senden("800,3,");
        this->uServer3->senden("999,1,");
        this->uServer3->senden(String100.str());
        this->uServer3->senden(StringSpielstand());
    }
    if(Spieler == 4){
        this->uServer4->initServer();
        //this->uServer4 = new Server("55316", breite, hoehe, Spieler, this);
        this->uServer4->start();
        this->uServer4->senden("800,4,");
        this->uServer4->senden("999,1,");
        this->uServer4->senden(String100.str());
        this->uServer4->senden(StringSpielstand());
    }
}

void Server::globalSend(string msg){
    cout << "Server Message To Send\t" << msg << endl;
    if(uServer1Connected){
        this->uServer1->senden(msg);
    }
    if(uServer2Connected){
        this->uServer2->senden(msg);
    }
    if(uServer3Connected){
        this->uServer3->senden(msg);
    }
    if(uServer4Connected){
        this->uServer4->senden(msg);
    }
}
void Server::SpielStandaktSenden(){
    if(uServer1Connected){
        this->uServer1->senden(StringSpielstand());
    }
    if(uServer2Connected){
        this->uServer2->senden(StringSpielstand());
    }
    if(uServer3Connected){
        this->uServer3->senden(StringSpielstand());
    }
    if(uServer4Connected){
        this->uServer4->senden(StringSpielstand());
    }
}

string Server::StringSpielstand(){
    string spielstand;
    stringstream anhang;
    stringstream sstr;
    spielstand = "500,";
    for(int i = 0; i < this->heigth; i++){
        for(int j = 0; j < this->width; j++){
            anhang << this->logic->getFields()[i][j];
            spielstand += anhang.str();
            spielstand += ",";

            anhang.str("");
        }
    }
    spielstand += "999,";
    sstr << this->logic->getAktPlayer();
    spielstand += sstr.str();
    spielstand += ",";
    sstr.str("");
    //cout << "Spielstand Senden: " << spielstand << endl;
    return spielstand;
}
void Server::setStoneControl(int spalte, int hoehe, int id){

    cout << "Server:\t\t" << "StoneControl ausgefuehrt" << endl;
    cout << spalte << " " << hoehe << " " << id << endl;
    if(this->logic->getAktPlayer() == id){
        this->logic->setField(spalte, hoehe);
    }
    SpielStandaktSenden();
}

void Server::NetSendNewClient(QString Name, int ID){
    stringstream id;
    string NewClient;
    id << ID;
    NewClient = "200," + Name.toStdString() + "," + id.str() + ",";
    AllClients.push_back(NewClient);
    cout << "Server:\t\tSenden Case " << NewClient;
    for(uint i = 0; i < AllClients.size(); i++){
        if(this->uServer1->connected){
            this->uServer1->senden(AllClients[i]);
        }
        if(this->uServer2->connected){
            this->uServer2->senden(AllClients[i]);
        }
        if(this->players >= 3){
            if(this->uServer3->connected){
                this->uServer3->senden(AllClients[i]);
            }
        }
        if(this->players == 4){
            if(this->uServer4->connected){
                this->uServer4->senden(AllClients[i]);
            }
        }
    }
}

void Server::NetSendSpielstandSL(){
    if(uServer1Connected){
        this->uServer1->senden(StringSpielstand());
    }
    if(uServer2Connected){
        this->uServer2->senden(StringSpielstand());
    }
    if(uServer3Connected){
        this->uServer3->senden(StringSpielstand());
    }
    if(uServer4Connected){
        this->uServer4->senden(StringSpielstand());
    }
}

void Server::NetSetServerConnectedSL(int server){
    if(server == 1){
        this->uServer1Connected = true;
    }
    else if(server == 2){
        this->uServer2Connected = true;
    }
    else if(server == 3){
        this->uServer3Connected = true;
    }
    else if(server == 4){
        this->uServer4Connected = true;
    }
}

