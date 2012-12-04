#include "superserver.h"
#include "server.h"
#include "Logic.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

SuperServer::SuperServer(int breite, int hoehe, int Spieler){
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


    this->uServer1 = new Server("55313", breite, hoehe, Spieler);
    this->uServer1->start();
    this->uServer1->senden(String100.str());
    this->uServer1->senden(StringSpielstand());


    this->uServer2 = new Server("55314", breite, hoehe, Spieler);
    this->uServer2->start();
    this->uServer2->senden(String100.str());
    this->uServer2->senden(StringSpielstand());

    if(Spieler >= 3){
        this->uServer3 = new Server("55315", breite, hoehe, Spieler);
        this->uServer3->senden(String100.str());
        this->uServer3->senden(StringSpielstand());
    }
    if(Spieler == 4){
        this->uServer4 = new Server("55316", breite, hoehe, Spieler);
        this->uServer4->senden(String100.str());
        this->uServer4->senden(StringSpielstand());
    }
}
void SuperServer::SpielStandaktSenden(){
    this->uServer1->senden(StringSpielstand());
    this->uServer2->senden(StringSpielstand());
    if(this->players >= 3){
        this->uServer3->senden(StringSpielstand());
    }
    if(this->players == 4){
        this->uServer4->senden(StringSpielstand());
    }
}

string SuperServer::StringSpielstand(){
    string spielstand;
    stringstream anhang;
    spielstand = "500,";
    for(int i = 0; i < this->heigth; i++){
        for(int j = 0; j < this->width; j++){
            anhang << this->fields[i][j];
            spielstand += anhang.str();
            spielstand += ",";
            anhang.str("");
        }
    }
    return spielstand;
}
void SuperServer::setStoneControl(int spalte, int hoehe, int id){

    cout << "StoneControl ausgefuehrt" << endl;
    cout << spalte << " " << hoehe << " " << id << endl;
    if(this->logic->getAktPlayer() == id){
        this->logic->setField(spalte, hoehe);
    }
    SpielStandaktSenden();
}
