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

    this->logic = new Logic(breite, hoehe, Spieler);
    this->logic->setInitStones();
    this->fields = this->logic->getFields();

    this->width = breite;
    this->heigth = hoehe;
    this->players = Spieler;
}



void Server::globalSend(string msg){
    cout << "Server Message To Send\t\t" << msg << endl;
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
        cout << "Anistones Groesse " << this->logic->getAniStones(-1).size() << endl;
        spielstand = "909,";
        for(uint k = 0; k < this->logic->getAniStones(-1).size(); k++){
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
		SpielStandaktSenden();
    }
    
    cout << "Server:\t\t" << "Code 900 UpdateWinvector" << endl;
    vector<int> winVector = this->logic->win();
    string winVectorString = "900,";
    for(uint i = 0; i < winVector.size(); i++){
        stringstream winVecNum;
        winVecNum << winVector[i];
        winVectorString += winVecNum.str() += ",";
    }
    //winVectorString << winVecNum.str();
    globalSend(winVectorString);
}

void Server::NetSendNewClient(QString Name, int ID){
    QVector<string> tmp;
    stringstream id;
    string NewClient;
    string clients = "";
    id << ID;
    NewClient = Name.toStdString() + "," + id.str() + ",";

    tmp.push_back(Name.toStdString());
    tmp.push_back(id.str());
    tmp.push_back(NewClient);

    AllClients.push_back(tmp);
    cout << "Server:\t\tSenden Case " << NewClient;
    clients += "200,";

    for(int i = 0; i < AllClients.size(); i++){
        clients += AllClients[i][2];
    }
    clients += "END__OF__LINE,";
    if(this->uServer1->connected){
        this->uServer1->senden(clients);
    }
    if(this->uServer2->connected){
        this->uServer2->senden(clients);
    }
     if(this->players >= 3){
        if(this->uServer3->connected){
        this->uServer3->senden(clients);
        }
    }
    if(this->players == 4){
        if(this->uServer4->connected){
        this->uServer4->senden(clients);
        }
    }
}

void Server::NetSendAllClientsSL(int del){
    cout << "Server:\t\t" << "Net Send All ClientsSL" << endl;
    stringstream blid;
    string id_string;
    blid << del;
    id_string = blid.str();

    for(int i = 0; i < AllClients.size(); i++){
        string tmo = AllClients[i][1];
        if(strcmp(tmo.c_str(), id_string.c_str()) == 0){
            AllClients.remove(i);
        }
    }

    string string_to_send;
    string_to_send = "200,";
    cout << "Server:\t\tCase 200:";
    for(int i = 0; i < AllClients.size(); i++){
        string_to_send += AllClients[i][2];
        cout << string_to_send;
    }
    cout << endl;
    string_to_send += "END__OF__LINE,";

    if(this->uServer1->connected){
        this->uServer1->senden(string_to_send);
    }
    if(this->uServer2->connected){
        this->uServer2->senden(string_to_send);
    }
    if(this->players >= 3){
        if(this->uServer3->connected){
            this->uServer3->senden(string_to_send);
        }
    }
    if(this->players == 4){
        if(this->uServer4->connected){
            this->uServer4->senden(string_to_send);
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

int Server::NetDestroyServer(int uServerNumber){
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
        return 1;
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
        return 2;
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
        return 3;
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
        return 4;
    }
    return 0;
}

