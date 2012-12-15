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
    QObject::connect(this->uServer1,SIGNAL(NetDisconnectServer(int)),this,SLOT(NetDestroyServer(int)));
    QObject::connect(this->uServer1,SIGNAL(NetSendAllClients(int)),this,SLOT(NetSendAllClientsSL(int)));

    QObject::connect(this->uServer2,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
    QObject::connect(this->uServer2,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
    QObject::connect(this->uServer2,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
    QObject::connect(this->uServer2,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));
    QObject::connect(this->uServer2,SIGNAL(NetDisconnectServer(int)),this,SLOT(NetDestroyServer(int)));
    QObject::connect(this->uServer2,SIGNAL(NetSendAllClients(int)),this,SLOT(NetSendAllClientsSL(int)));

    if(Spieler >= 3){
        QObject::connect(this->uServer3,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
        QObject::connect(this->uServer3,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
        QObject::connect(this->uServer3,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
        QObject::connect(this->uServer3,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));
        QObject::connect(this->uServer3,SIGNAL(NetDisconnectServer(int)),this,SLOT(NetDestroyServer(int)));
        QObject::connect(this->uServer3,SIGNAL(NetSendAllClients(int)),this,SLOT(NetSendAllClientsSL(int)));

    }
    if(Spieler == 4){
        QObject::connect(this->uServer4,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
        QObject::connect(this->uServer4,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
        QObject::connect(this->uServer4,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
        QObject::connect(this->uServer4,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));
        QObject::connect(this->uServer4,SIGNAL(NetDisconnectServer(int)),this,SLOT(NetDestroyServer(int)));
        QObject::connect(this->uServer4,SIGNAL(NetSendAllClients(int)),this,SLOT(NetSendAllClientsSL(int)));

    }
    this->uServer1Connected = false;
    this->uServer2Connected = false;
    this->uServer3Connected = false;
    this->uServer4Connected = false;

    /*stringstream String100;
    String100 << "100,";
    String100 << breite;
    String100 << ",";
    String100 << hoehe;
    String100 << ",";
    String100 << Spieler;
    String100 << ",";
    cout << String100.str() << endl;*/


    this->logic = new Logic(breite, hoehe, Spieler);
    this->logic->setInitStones();
    this->fields = this->logic->getFields();

    this->width = breite;
    this->heigth = hoehe;
    this->players = Spieler;
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

    //vor dem Spielstand muss die animation geladen werden
    if(this->logic->getAniStones(-1).size() > 0){
        spielstand = "909,";
        for(int k = 0; k < this->logic->getAniStones(-1).size(); k++){
            anhang << this->logic->getAniStones(-1)[k];
            spielstand += anhang.str();
            spielstand += ",";
            anhang.str("");
        }
    }



    spielstand += "500,";
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
    cout << "Spielstand Senden: " << spielstand << endl;
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

void Server::NetSendAllClientsSL(int del){
    vector<string> nerv;
    for(uint i = 0; i<AllClients.size();i++){
        string bla = AllClients[i];
        if(atoi(&bla[bla.length()-2]) != del){
            nerv.push_back(AllClients[i]);
        }
    }
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

void Server::NetDestroyServer(int uServerNumber){
    if(uServerNumber == 1){
        this->uServer1->disconnect();
        this->uServer1->terminate();
        this->uServer1->wait();
        this->uServer1->~subServer();
        this->uServer1 = new subServer(this,"55313", this->width, this->heigth, this->players, 1);
        this->uServer1Connected = false;

        QObject::connect(this->uServer1,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
        QObject::connect(this->uServer1,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
        QObject::connect(this->uServer1,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
        QObject::connect(this->uServer1,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));
        QObject::connect(this->uServer1,SIGNAL(NetDisconnectServer(int)),this,SLOT(NetDestroyServer(int)));
        QObject::connect(this->uServer1,SIGNAL(NetSendAllClients(int)),this,SLOT(NetSendAllClientsSL(int)));

        emit NetNewServer(1);
    }
    else if(uServerNumber == 2){
        this->uServer2->disconnect();
        this->uServer2->terminate();
        this->uServer2->wait();
        this->uServer2->~subServer();
        this->uServer2 = new subServer(this,"55314", this->width, this->heigth, this->players, 2);
        this->uServer2Connected = false;

        QObject::connect(this->uServer2,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
        QObject::connect(this->uServer2,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
        QObject::connect(this->uServer2,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
        QObject::connect(this->uServer2,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));
        QObject::connect(this->uServer2,SIGNAL(NetDisconnectServer(int)),this,SLOT(NetDestroyServer(int)));
        QObject::connect(this->uServer2,SIGNAL(NetSendAllClients(int)),this,SLOT(NetSendAllClientsSL(int)));

        emit NetNewServer(2);
    }
    else if(uServerNumber == 3){
        this->uServer3->disconnect();
        this->uServer3->terminate();
        this->uServer3->wait();
        this->uServer3->~subServer();
        this->uServer3 = new subServer(this,"55315", this->width, this->heigth, this->players, 3);
        this->uServer3Connected = false;

        QObject::connect(this->uServer3,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
        QObject::connect(this->uServer3,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
        QObject::connect(this->uServer3,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
        QObject::connect(this->uServer3,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));
        QObject::connect(this->uServer3,SIGNAL(NetDisconnectServer(int)),this,SLOT(NetDestroyServer(int)));
        QObject::connect(this->uServer3,SIGNAL(NetSendAllClients(int)),this,SLOT(NetSendAllClientsSL(int)));

        emit NetNewServer(3);
    }
    else if(uServerNumber == 4){
        this->uServer4->disconnect();
        this->uServer4->terminate();
        this->uServer4->wait();
        this->uServer4->~subServer();
        this->uServer4 = new subServer(this,"55316", this->width, this->heigth, this->players, 4);
        this->uServer4Connected = false;

        QObject::connect(this->uServer4,SIGNAL(setStone(int, int, int)),this,SLOT(setStoneControl(int, int, int)));
        QObject::connect(this->uServer4,SIGNAL(NetServerNewClient(QString, int)),this,SLOT(NetSendNewClient(QString,int)));
        QObject::connect(this->uServer4,SIGNAL(NetSendSpielstand()),this,SLOT(NetSendSpielstandSL()));
        QObject::connect(this->uServer4,SIGNAL(NetSetServerConnected(int)),this,SLOT(NetSetServerConnectedSL(int)));
        QObject::connect(this->uServer4,SIGNAL(NetDisconnectServer(int)),this,SLOT(NetDestroyServer(int)));
        QObject::connect(this->uServer4,SIGNAL(NetSendAllClients(int)),this,SLOT(NetSendAllClientsSL(int)));

        emit NetNewServer(4);
    }
}

