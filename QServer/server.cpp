#include "server.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Server::Server(string port, int breite, int hoehe){
    this->fields.assign(hoehe,vector<int>(breite,0));
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            this->fields[i][j] = 0;
        }
    }


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

    while(1){
        if(this->sock2.recv(this->empfang)){
            cout << this->empfang << endl;
        }
    }

    cout << this->empfang << endl;
}
void Server::ausfuehren(string nachricht){

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
    spielstand = "500";
    for(int i = 0; i < this->hoehe; i++){
        for(int j = 0; j < this->breite; j++){
            anhang << this->fields[i][j];
            spielstand += ",";
            spielstand += anhang.str();
            anhang.str("");
        }
    }
    return spielstand;
}
