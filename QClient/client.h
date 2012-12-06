#ifndef CLIENT_H
#define CLIENT_H
#include <QThread>
#include "socket.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Client: public QThread{
    Q_OBJECT
public:
    Client(string host,bool debug_mode);
    void senden(string mes);
    void run();
    int width;
    int height;
    int getAktPlayer();
    bool debug_mode;
private:
    string name;
    int id, players;
    bool running;
    vector<vector<int> > fields;
    vector<string> explode(const string& str, char delimiter);
    Socket client;
    int aktPlayer;
    vector<string> playersNames;
    std::string werte;

};

#endif // CLIENT_H
