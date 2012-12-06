#include "client.h"
#include "socket.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>


using namespace std;

Client::Client(string host, bool debug_mode = false){
    this->debug_mode = debug_mode;
    this->running = false;
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
            //cout << s << endl;
            //vector<string> empfangen;
            if(s.length() > 0){
                max = count(s.begin(), s.end(), ',')-1;

                while(abschnitt < max){


                    switch(atoi(explode(s, ',')[abschnitt].c_str())){
                    //breite, hoehe, anzSpieler
                    case 100:
                        //cout << "100 getroffen" << endl;
                        this->width = atoi(explode(s, ',')[abschnitt+1].c_str());
                        this->height =atoi(explode(s, ',')[abschnitt+2].c_str());
                        this->players = atoi(explode(s, ',')[abschnitt+3].c_str());
                        abschnitt+=4;
                        //cout << "Spiel ist " << this->width << " breit und " << this->height << "hoch "<< endl;
                        this->fields.assign(this->height,vector<int>(this->width,0));
                        break;
                    //Spielername, id <-vom server zugewiesen
                    case 200:
                        //cout << "Case 200 wurde aufgerufen"<< endl;

                        this->playersNames[atoi(explode(s, ',')[abschnitt+2].c_str())] = explode(s, ',')[abschnitt+1].c_str();
                        //cout << "Neuer Spielername aufgenommen: " <<  this->playersNames[atoi(explode(s, ',')[abschnitt+2].c_str())] << endl;
                        abschnitt+=3;

                        emit NetPlayersNames(this->playersNames);
                        break;
                    //Spieler weg
                    case 201:
                        break;
                    //Spielstart
                    case 400:
                        this->running = true;
                        abschnitt+=2;
                        emit NetGameStart();

                        break;
                    //Status
                    case 300:
                        break;
                    //Feldarray
                    case 500:
                        //cout << "500 getroffen" << endl;
                        //cout << "Abschnitt zahl: " << abschnitt << endl;
                        //cout << s << endl;
                        for(int i = 0; i < this->height; i++){
                            for(int j = 0; j < this->width; j++){
                                this->fields[i][j] = atoi(explode(s, ',')[abschnitt+index].c_str());
                                index++;
                            }
                        }

                        abschnitt+=index;
                        /*
                        for(int i = 0; i < this->height; i++){
                            for(int j = 0; j < this->width; j++){
                                cout << this->fields[i][j] << " ";
                            }
                            cout << endl;
                        }
                        cout << "Eigene id" << this->id << endl;
                        */

                        index = 1;
                        emit NetNewField(this->fields);

                    break;

                    //id vom Server zugewiesen
                    case 800:
                        //cout << "800 getroffen" << endl;
                        //cout << "neue id: " << atoi(explode(s, ',')[abschnitt+1].c_str()) << endl;

                        this->id = atoi(explode(s, ',')[abschnitt+1].c_str());


                        abschnitt+=2;

                        break;
                    //winvector
                    case 900:


                        //emit NetWinVector(QVector<int>);
                        break;

                    case 999:
                        //cout << "999 ausgelöst" << endl;
                        this->aktPlayer = atoi(explode(s, ',')[abschnitt+1].c_str());
                        //cout << "Spieler " << this->aktPlayer << " ist dran" << endl;
                        abschnitt+=2;

                        emit NetAktPlayer(this->aktPlayer);
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
int Client::getAktPlayer(){
    return this->aktPlayer;
}
void Client::setStoneClient(int x, int y){
    if(this->debug_mode){
        cout << "x: "<< x << " Y: " << y  << endl;
    }
    stringstream sstrX, sstrY, sstrID;
    string zuSenden;
    sstrX << x;
    sstrY << y;
    sstrID << this->id;
    zuSenden = "600,";
    zuSenden += sstrX.str();
    zuSenden += ",";
    zuSenden += sstrY.str();
    zuSenden += ",";
    zuSenden += sstrID.str();
    zuSenden += ",";

    if(this->debug_mode){
        cout << "zu Senden: " << zuSenden << endl;
    }
    senden(zuSenden);
}

void Client::senden(string mes){
    if(debug_mode){
        if(mes == ""){
            string mes;
            string x;
            string y;
            string senden;
            stringstream sstr;
            stringstream sstrY;
            do {

                cout << "X: ";
                cin >> x;
                cout << "Y: ";
                cin >> y;
                cout << endl;
                senden = "600,";
                senden += x;
                senden += ",";
                senden += y;
                senden += ",";
                sstr << this->id;
                senden += sstr.str();
                senden += ",";
                sstr.str("");

                cout << "das soll gesendet werden " << senden << endl;

                this->client.send(senden);
                cout << this->getAktPlayer() << " ist dran " << endl;

                cout << "die eigene id: " << this->id <<endl;

            } while( mes != "quit" );
        }
        else{
            this->client.send(mes);
        }
        //this->client.close();
    }
    else{
        this->client.send(mes);
    }
}

vector<string> Client::explode(const string& str, char delimiter){
    vector<string> tokens;
    stringstream tokenStream(str);
    string tempStr;

    while(getline(tokenStream, tempStr, delimiter))
        tokens.push_back(tempStr);

    return tokens;
}
