#include "client.h"
#include "socket.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>


using namespace std;

Client::Client(string host){

    string s;
    this->client.create();
    this->client.connect( host, 55312);
    this->client.recv(s);

    stringstream sstr(s);

    int port;
    sstr >> port;

    this->client.close();


    try {
        this->client.create();


        this->client.connect( host, port );

    }
    catch ( SockExcept& e ) {
        cout << "Eine Exception wurde abgefangen: " << e.get_SockExcept() << endl;
    }
}
void Client::run(){
    string s;

    int abschnitt = 0;
    int index = 1;
    int max;



    while(1){
        this->client.recv(s);
            cout << s << endl;
            vector<string> empfangen;
            if(s.length() > 0){
                max = count(s.begin(), s.end(), ',')-1;

                while(abschnitt < max){


                    switch(atoi(explode(s, ',')[abschnitt].c_str())){
                    //breite, hoehe, anzSpieler
                    case 100:
                        this->width = atoi(explode(s, ',')[abschnitt+1].c_str());
                        this->height =atoi(explode(s, ',')[abschnitt+2].c_str());
                        abschnitt+=3;
                        this->fields.assign(this->height,vector<int>(this->width,0));
                        break;
                    //Spielername, id <-vom server zugewiesen
                    case 200:
                        this->spielerName = explode(s, ',')[abschnitt+1].c_str();
                        this->id = atoi(explode(s, ',')[abschnitt+2].c_str());
                        abschnitt+=3;
                        cout << "Spielername: " << this->spielerName << endl;
                        break;
                    //Spieler weg
                    case 201:
                        break;
                    //Spielstart
                    case 400:

                        break;
                    //Status
                    case 300:
                        break;
                    //Feldarray
                    case 500:
                        //cout << "eingestiegen" << endl;
                        for(int i = 0; i < this->height; i++){
                            for(int j = 0; j < this->width; j++){
                                this->fields[i][j] = atoi(explode(s, ',')[abschnitt+index].c_str());
                                index++;
                            }
                        }
                        abschnitt+=index+1;
                        cout << "feld geschicktz" << endl;
                        for(int i = 0; i < this->height; i++){
                            for(int j = 0; j < this->width; j++){
                                cout << this->fields[i][j] << " ";
                            }
                            cout << endl;
                        }
                        this->feldDa = 1;
                        index = 1;
                    break;

                    //id vom Server zugewiesen
                    case 800:
                        break;
                    //winvector
                    case 900:
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

void Client::ausfuehren(){

    string mes;
    do {
        if(this->werte.length() > 0){
            cout << this->werte << endl;
        }
        cout << "Nachricht zum Versenden: ";
        getline( cin, mes, '\n' );
        this->client.send( mes );
        cout << "Hoehe: " << this->height << endl;
        cout << "Breite: " << this->width<< endl;
        if(this->feldDa == 1){
            cout << "Felder fertig" << endl;
            cout << "Feld: " << this->fields[0][0] << endl;
        }
    } while( mes != "quit" );
    this->client.close();
}
vector<string> Client::explode(const string& str, char delimiter){
    vector<string> tokens;
    stringstream tokenStream(str);
    string tempStr;

    while(getline(tokenStream, tempStr, delimiter))
        tokens.push_back(tempStr);

    return tokens;
}
