#include "server.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Server::Server(string port, int breite, int hoehe, int anzSpieler){
    //this->fields.assign(hoehe,vector<int>(breite,0));
    /*
    this->ThreadLogic = new Logic(breite, hoehe, anzSpieler);
    this->ThreadLogic->setInitStones();
    this->fields = this->ThreadLogic->getFields();
    */

    this->breite = breite;
    this->hoehe = hoehe;
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
                    //breite, hoehe, anzSpieler
                    case 100:
                        this->width = atoi(explode(s, ',')[abschnitt+1].c_str());
                        this->height =atoi(explode(s, ',')[abschnitt+2].c_str());
                        abschnitt+=3;
                        this->fields.assign(this->height,vector<int>(this->width,0));
                        break;
                    //Spielername, id <-vom server zugewiesen
                    /*case 200:
                        this->spielerName = explode(s, ',')[abschnitt+1].c_str();
                        this->id = atoi(explode(s, ',')[abschnitt+2].c_str());
                        abschnitt+=3;
                        cout << "Spielername: " << this->spielerName << endl;
                        break;
                    */
                    //Spieler weg
                    case 201:
                        break;
                    //Spielstart
                    case 400:

                        break;
                    //Status
                    case 300:
                        break;


                    //id vom Server zugewiesen
                    case 800:
                        break;

                    //winvector
                    case 900:
                        break;

                    case 600:
                        cout << "in600spalte" << endl;
                        int zeile, spalte,id;

                        spalte = atoi(explode(s, ',')[abschnitt+1].c_str());
                        zeile = atoi(explode(s, ',')[abschnitt+2].c_str());
                        id = atoi(explode(s, ',')[abschnitt+3].c_str());


                        cout << "Client " << id << "will seitzen auf: x="<<spalte<<" y="<<zeile<<endl;
                        abschnitt+=4;
                        if(id == this->aktPlayer){

                            this->ThreadLogic->setField(spalte, zeile);
                            this->fields = this->ThreadLogic->getFields();
                            //senden(StringSpielstand());
                        }
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
