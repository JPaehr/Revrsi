#include "server.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Server::Server(QObject *parent, string port, int breite, int hoehe, int anzSpieler) : QThread(parent){
    //this->fields.assign(hoehe,vector<int>(breite,0));
    /*
    this->ThreadLogic = new Logic(breite, hoehe, anzSpieler);
    this->ThreadLogic->setInitStones();
    this->fields = this->ThreadLogic->getFields();
    */
    this->breite = breite;
    this->hoehe = hoehe;
    this->port = port;
}
void Server::initServer(){
    cout << "Hier war ich Server" << endl;
    this->sock1.create();
    cout << "Server erstellt" << endl;
    this->sock1.bind(55312);
    cout << "Server gebunden" << endl;
    this->sock1.listen();
    cout << "Server hoert zu" << endl;
    this->sock1.accept(this->sock2);
    cout << "Server akzeptiert" << endl;
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
}

void Server::run(){
    string s;

    int abschnitt = 0;
    int index = 1;
    int max;

    while(1){
        if(this->sock2.recv(s)){
            cout << s << endl;
            vector<string> empfangen;
            if(s.length() > 0){
                max = count(s.begin(), s.end(), ',')-1;

                while(abschnitt < max){

                    cout << "aktueller erster wert: " << atoi(explode(s, ',')[abschnitt].c_str()) << endl;
                    switch(atoi(explode(s, ',')[abschnitt].c_str())){

                    //Spieler weg
                    case 201:
                        break;
                    //Spielstart

                    //Status
                    case 300:
                        break;

                    case 222:
                        if(this->id == atoi(explode(s, 's')[abschnitt+2].c_str())){
                            this->name = explode(s, ',')[abschnitt+1].c_str();
                        }
                        else{
                            cout << "Client mit nicht zugewiesener oder falscher id hat versucht seinen Name zu verschicken" << endl;
                            cout << "empfangene id: " << atoi(explode(s, 's')[abschnitt+2].c_str()) << endl;
                            cout << "eigentliche id: " << this->id;
                        }

                    //breite, hoehe, id von Client an Server
                    case 600:
                        cout << "in600spalte" << endl;
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
                index = 1;


            }
            s.clear();

        }
    }

    cout << this->empfang << endl;
}
void Server::senden(string nachricht){

    this->sock2.send( nachricht );
}
vector<vector<int> > Server::getFelder(){
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

string Server::StringSpielstand(){
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

vector<string> Server::explode(const string& str, char delimiter){
    vector<string> tokens;
    stringstream tokenStream(str);
    string tempStr;

    while(getline(tokenStream, tempStr, delimiter))
        tokens.push_back(tempStr);

    return tokens;
}
