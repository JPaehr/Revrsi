#ifndef CLIENT_H
#define CLIENT_H
#include <QThread>
#include "../socket.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Client: public QThread{
    Q_OBJECT
public:
    Client(string host);
    void senden(string mes);
    void run();
    int width;
    int height;
    int getAktPlayer();
private:
    string name;
    int id, players;
    bool running;
    vector<vector<int> > fields;
    vector<string> explode(const string& str, char delimiter);
    Socket client;
    int aktPlayer;
    vector<string> playersNames;
    string werte;

signals:
    void fieldChange(vector<vector<int> >);

};

#endif // CLIENT_H
