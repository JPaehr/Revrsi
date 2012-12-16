#include "subServer.h"
#include <iostream>
#include <sstream>
//#include <vector>
#include "server.h"

using namespace std;

subServer::subServer(QObject *parent, string port, int breite, int hoehe, int anzSpieler, int ID) : QThread(parent){
    //this->fields.assign(hoehe,vector<int>(breite,0));
    /*
    this->ThreadLogic = new Logic(breite, hoehe, anzSpieler);
    this->ThreadLogic->setInitStones();
    this->fields = this->ThreadLogic->getFields();
    */
    this->breite = breite;
    this->hoehe = hoehe;
    this->spieler_num = anzSpieler;
    this->port = port;
    this->id = ID;
    this->connected = false;
    this->clientListSend = false;
}

subServer::~subServer(){
}

/*void subServer::initServer(){
    //cout << "Hier war ich Server" << endl;
    this->sock1.create();
    cout << "Server:\t\tSocket 1 erstellt" << endl;
    this->sock1.bind(55312);
    cout << "Server:\t\tSocket 1 an Port 55312 gebunden" << endl;
    this->sock1.listen();
    cout << "Server:\t\tWarte auf Client" << endl;
    this->sock1.accept(this->sock2);
    cout << "Server:\t\tClient Akzeptiert. Verbindung wird aufgebaut..." << endl;
    this->sock2.send(port);

    this->sock2.close();
    this->sock1.close();

    this->sock1.create();

    stringstream sstr(port);

    int nport;
    sstr >> nport;

    this->sock1.bind(nport);
    this->sock1.listen();
    this->sock1.accept(this->sock2);
    //this->connected = true;
}*/

void subServer::run(){
    //cout << "Hier war ich Server" << endl;
    this->sock1.create();
    cout << "Server:\t\tSocket 1 erstellt" << endl;
    this->sock1.bind(55312);
    cout << "Server:\t\tSocket 1 an Port 55312 gebunden" << endl;
    this->sock1.listen();
    cout << "Server:\t\tWarte auf Client" << endl;
    this->sock1.accept(this->sock2);
    cout << "Server:\t\tClient Akzeptiert. Verbindung wird aufgebaut..." << endl;
    this->sock2.send(port);

    this->sock2.close();
    this->sock1.close();

    this->sock1.create();

    stringstream sstr(port);

    int nport;
    sstr >> nport;

    this->sock1.bind(nport);
    this->sock1.listen();
    this->sock1.accept(this->sock2);
    this->connected = true;
    emit this->NetSetServerConnected(this->id);

    stringstream String800;
    String800 << "800," << this->id << ",";
    //this->senden("800,1,");
    this->senden(String800.str());
    this->senden("999,1,");




    stringstream String100;
    String100 << "100,";
    String100 << this->breite;
    String100 << ",";
    String100 << this->hoehe;
    String100 << ",";
    String100 << this->spieler_num;
    String100 << ",";
    cout << String100.str() << endl;


    this->senden(String100.str());

    emit this->NetSendSpielstand();







    string s;

    int abschnitt = 0;
    //int index = 1;
    int max;

    while(1){
        if(this->sock2.recv(s)){
            cout << "Server:\t\tReceived String: " << s << endl;
            vector<string> empfangen;
            if(s.length() > 0){
                max = count(s.begin(), s.end(), ',')-1;

                while(abschnitt < max){

                    cout << "Server:\t\tZu bearbeitender Case: " << atoi(explode(s, ',')[abschnitt].c_str()) << endl;
                    switch(atoi(explode(s, ',')[abschnitt].c_str())){

                    //Spieler weg
                    case 201:
                        cout << "Case 201 bearbeiten. Player Disconnect." << endl;
                        cout << "Player mit ID: " << atoi(explode(s, ',')[abschnitt+1].c_str()) << " wurde getrennt" << endl;
                        this->connected = false;
                        emit NetSendAllClients(atoi(explode(s, ',')[abschnitt+1].c_str()));
                        this->sleep(1);
                        emit NetDisconnectServer(atoi(explode(s, ',')[abschnitt+1].c_str()));
                        abschnitt += 2;
                        cout << "Case 201 verarbeitet" << endl;
                        break;
                    //Spielstart

                    //Status
                    case 300:
                        break;

                    case 222:
                        cout << "Server:\t\tCase 222 bearbeiten. Spielername und Client ID erwartet." << endl;
                        if(this->id == atoi(explode(s, ',')[abschnitt+2].c_str())){
                            this->name = explode(s, ',')[abschnitt+1].c_str();
                            QString nnn = QString::fromStdString(this->name);
                            //cout << this->name;
                            /*vector<string> vec;
                            stringstream sstrID;
                            //nnn = QString(this->name);
                            sstrID << this->id;
                            vec.push_back(this->name);
                            vec.push_back(sstrID.str());
                            this->players.push_back(vec);*/
                            emit this->NetServerNewClient(nnn, this->id);
                            cout << "Server:\t\tCase 222 verarbeitet. Bekommen Name: " << this->name << " ID: " << this->id << " EMIT NetServerNewClient" << endl;
                        }
                        else{
                            cout << "Client mit nicht zugewiesener oder falscher id hat versucht seinen Name zu verschicken" << endl;
                            cout << "empfangene id: " << atoi(explode(s, 's')[abschnitt+2].c_str()) << endl;
                            cout << "eigentliche id: " << this->id;
                        }
                        abschnitt += 3;
                            break;

                    //breite, hoehe, id von Client an Server
                    case 600:
                        cout << "Server hat empfangen CODE 600\nGeklicktes Feld";
                        //cout << "in600spalte" << endl;
                        int zeile, spalte,id;

                        spalte = atoi(explode(s, ',')[abschnitt+1].c_str());
                        zeile = atoi(explode(s, ',')[abschnitt+2].c_str());
                        id = atoi(explode(s, ',')[abschnitt+3].c_str());


                        cout << "Client " << id << " will setzen auf: x = "<<spalte << " y = "<< zeile << endl;
                        abschnitt+=4;
                        /*if(id == this->aktPlayer){

                            this->ThreadLogic->setField(spalte, zeile);
                            this->fields = this->ThreadLogic->getFields();
                            //senden(StringSpielstand());
                        }*/
                        cout << "emit ab hier" << endl;
                        emit this->setStone(spalte, zeile, id);

                        break;
                    default:
                        break;

                    }
                }
                abschnitt = 0;
                //index = 1;


            }
            s.clear();

        }
    }

    cout << this->empfang << endl;
}
void subServer::senden(string nachricht){

    this->sock2.send( nachricht );
}
vector<vector<int> > subServer::getFelder(){
    return this->fields;
}
string implode( const string &glue, const vector<string> &pieces )
{
    string a;
    int leng=pieces.size();
    for(int i=0; i<leng; i++)
    {
        a+= pieces[i];
        if (  i < (leng-1) )
            a+= glue;
    }
    return a;
}

string subServer::StringSpielstand(){
    string spielstand;
    stringstream anhang;
    spielstand = "500,";
    for(int i = 0; i < this->hoehe; i++){
        for(int j = 0; j < this->breite; j++){
            anhang << this->fields[i][j];
            spielstand += anhang.str();
            spielstand += ",";
            anhang.str("");
        }
    }
    return spielstand;
}

vector<string> subServer::explode(const string& str, char delimiter){
    vector<string> tokens;
    stringstream tokenStream(str);
    string tempStr;

    while(getline(tokenStream, tempStr, delimiter))
        tokens.push_back(tempStr);

    return tokens;
}
