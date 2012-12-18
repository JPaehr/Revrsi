#include "client.h"
//#include "socket.h"
//#include "../QServer/socket.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>


using namespace std;

Client::Client(string host, bool debug_mode){
    this->debug_mode = debug_mode;
    this->running = false;
    this->runtime = 0;
    this->ConnectedClients = 0;
    this->disconnectSend = false;
    string s;
    qRegisterMetaType<QVector<QString> >("QVector<QString>");
    qRegisterMetaType<QVector<int> >("QVector<int>");

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

Client::~Client(){
}

void Client::run(){
    string s;

    int abschnitt = 0;
    int index = 1;
    int max;
    int winPlus = 0;
	int dazu;
    //QVector<string> str;
    while(1){
        this->client.recv(s);
        //if(debug_mode){cout << "Client:\t\t" << "Received: " << s << endl;}
            //cout << s << endl;
            //vector<string> empfangen;
            if(s.length() > 0){
                max = count(s.begin(), s.end(), ',');
                if(max > 1){max--;}
                while(abschnitt < max){


                    switch(atoi(explode(s, ',')[abschnitt].c_str())){
                    //breite, hoehe, anzSpieler
                    case 100:
                        if(debug_mode){cout << "Client:\t\t" << "Case 100 bearbeiten" << endl;}
                        this->width = atoi(explode(s, ',')[abschnitt+1].c_str());
                        this->height =atoi(explode(s, ',')[abschnitt+2].c_str());
                        this->players = atoi(explode(s, ',')[abschnitt+3].c_str());
                        abschnitt+=4;
                        //cout << "Spiel ist " << this->width << " breit und " << this->height << "hoch "<< endl;
                        this->fields.assign(this->height,vector<int>(this->width,0));
                        this->runtime++;
                        emit NetGameValues(this->width, this->height, this->players);
                        if(debug_mode){cout << "Client:\t\t" << "Case 100 verarbeitet\t" << "EMIT: NetGameValues" << endl;}
                        break;
                    //Spielername, id <-vom server zugewiesen
                    case 200:
                        if(debug_mode){cout << "Client:\t\t" << "Case 200 bearbeiten" << endl;}
                        this->playersNames.clear();
                        for(int i = 1; ; i+=2){
                            if(strcmp(explode(s, ',')[abschnitt+i].c_str(),"END__OF__LINE") != 0){
                                this->playersNames.push_back(explode(s, ',')[abschnitt+i].c_str());
                                this->playersNames.push_back(explode(s, ',')[abschnitt+(i+1)].c_str());
                            }
                            else{
                                emit this->NetPlayersNames(this->playersNames);
                                this->ConnectedClients++;
                                if(debug_mode){cout << "Client:\t\t" << "Case 200 verarbeitet\t" << "EMIT: NetPlayerNames" << endl;}
                                abschnitt += i;
                                break;
                            }
                        }
                        //this->playersNames.push_back(str);
                        //cout << "Neuer Spielername aufgenommen: " <<  this->playersNames[atoi(explode(s, ',')[abschnitt+2].c_str())] << endl;
                        //abschnitt+=3;

                        break;
                    //Spieler weg
                    case 201:
                        if(debug_mode){cout << "Client:\t\t" << "Case 201 bearbeiten" << endl;}
                        if(debug_mode){cout << "Client:\t\t" << "Case 201 verarbeitet\t" << endl;}
                        break;
                    //Spielstart
                    case 400:
                        if(debug_mode){cout << "Client:\t\t" << "Case 400 bearbeiten" << endl;}
                        
						this->running = true;                 
						abschnitt+=1;
                        emit NetServerWantGameStart();
                        if(debug_mode){cout << "Client:\t\t" << "Case 400 verarbeitet\t" << "EMIT: NetGameStart" << endl;}

                        break;
                    //Status
                    case 300:
                        if(debug_mode){cout << "Client:\t\t" << "Case 300 bearbeiten" << endl;}
                        if(debug_mode){cout << "Client:\t\t" << "Case 300 verarbeitet\t" << endl;}
                        break;
                    //Feldarray
                    case 500:
                        if(debug_mode){cout << "Client:\t\t" << "Case 500 bearbeiten" << endl;}
                        //cout << "Abschnitt zahl: " << abschnitt << endl;
                        //cout << s << endl;
                        for(int i = 0; i < this->height; i++){
                            for(int j = 0; j < this->width; j++){
                                this->fields[i][j] = atoi(explode(s, ',')[abschnitt+index].c_str());
                                index++;
                            }
                        }

                        abschnitt+=index;                       
						if(debug_mode){
                            for(int i = 0; i < this->height; i++){
                                for(int j = 0; j < this->width; j++){
                                    cout << this->fields[i][j] << " ";
                                }
                                cout << endl;
                            }
                            /*cout << "Eigene id" << this->id << endl;
                            */
                        }						
                        index = 1;
                        this->runtime++;
                        emit NetNewField();

                        if(debug_mode){cout << "Client:\t\t" << "Case 500 verarbeitet\t" << "EMIT: NetNewField" << endl;}
                        break;

                    //id vom Server zugewiesen
                    case 800:
                        if(debug_mode){cout << "Client:\t\t" << "Case 800 bearbeiten" << endl;}
                        //cout << "neue id: " << atoi(explode(s, ',')[abschnitt+1].c_str()) << endl;

                        this->id = atoi(explode(s, ',')[abschnitt+1].c_str());


                        abschnitt+=2;
                        emit NetGotID(this->id);
                        this->runtime++;
                        if(debug_mode){cout << "Client:\t\t" << "Case 800 verarbeitet\t" << "EMIT: NetGotID" << endl;}
                        break;
                    //winvector
                    case 900:
                        if(debug_mode){cout << "Client:\t\t" << "Case 900 bearbeiten" << endl;}
                        this->winVector.clear();
                        winPlus = 0;

                        this->winVector.push_back(atoi(explode(s, ',')[abschnitt+1].c_str()));
                        this->winVector.push_back(atoi(explode(s, ',')[abschnitt+2].c_str()));
                        this->winVector.push_back(atoi(explode(s, ',')[abschnitt+3].c_str()));
                        winPlus = 4;
                        if(this->players >= 3){
                            this->winVector.push_back(atoi(explode(s, ',')[abschnitt+4].c_str()));
                            winPlus= 5;
                        }
                        if(this->players == 4){
                            this->winVector.push_back(atoi(explode(s, ',')[abschnitt+5].c_str()));
                            winPlus= 6;
                        }

                        abschnitt+=winPlus;



                        emit NetWinVector(winVector);
                        if(debug_mode){cout << "Client:\t\t" << "Case 900 verarbeitet\t" << "EMIT: NetWinVector" << endl;}
                        break;

                    case 999:
                        if(debug_mode){cout << "Client:\t\t" << "Case 999 bearbeiten" << endl;}

                        this->aktPlayer = atoi(explode(s, ',')[abschnitt+1].c_str());
                        if(this->debug_mode){
                            cout << "Client:\t\t"<< "Spieler " << this->aktPlayer << " ist dran" << endl;

                        }
                        abschnitt+=2;

                        emit NetAktPlayer(this->aktPlayer);
                        this->runtime++;
                        if(debug_mode){cout << "Client:\t\t" << "Case 999 verarbeitet\t" << "EMIT: NetAktPlayer" << endl;}
                        break;						
					//Animationscode x, y, x, y, -10
                    case 909:
                        if(debug_mode){cout << "Client:\t\t" << "Case 909 bearbeiten" << endl;}


                        dazu = 1;

                        while((atoi(explode(s, ',')[abschnitt+dazu].c_str())) < 100 && strcmp(explode(s, ',')[abschnitt+dazu].c_str(), "") != 0){
                            this->VecAnimation.push_back(atoi(explode(s, ',')[abschnitt+dazu].c_str()));
                            dazu++;
                        }
                        abschnitt+= dazu;
                        cout << "Abschnitt: " << dazu << endl;

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

void Client::sendNameClient(QString ownName){
    if(this->debug_mode){
        cout << "Client:\t\t" << "Case 222 bearbeiten\t" << "Eigenen Namen + ID senden:\t" << "Name: " << QString(ownName).toStdString() << "\tID: " << this->id << endl;
    }
    stringstream sstrID;
    string zuSenden;
    sstrID << this->id;
    zuSenden = "222,";
    zuSenden += ownName.toStdString();
    zuSenden += ",";
    zuSenden += sstrID.str();
    zuSenden += ",";

    if(this->debug_mode){
        cout << "Client:\t\t" << "Case 222 verarbeitet\t" << endl;
    }
    senden(zuSenden);
}

vector<vector<int> > Client::getFields(){
    return this->fields;
}

void Client::senden(string mes){
    if(this->debug_mode){
    string mes;
        string x;
        string y;
        string senden;
        stringstream sstr;
        stringstream sstrY;
        do {
            /*for(int i = 0; i < this->height; i++){
                for(int j = 0; j < this->width; j++){
                    cout << this->fields[i][j] << " ";
                }
                cout << endl;
            }*/

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
}

vector<string> Client::explode(const string& str, char delimiter){
    vector<string> tokens;
    stringstream tokenStream(str);
    string tempStr;

    while(getline(tokenStream, tempStr, delimiter))
        tokens.push_back(tempStr);

    return tokens;
}
