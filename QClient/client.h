#ifndef CLIENT_H
#define CLIENT_H
#include <QThread>
#include "socket.h"
#include <string>
#include <iostream>
#include <vector>
#include <QVector>

using namespace std;

class Client: public QThread{
    Q_OBJECT
public:
    Client(string host, bool debug_mode);
    void senden(string mes);
    void run();
    int width;
    int height;
    int getAktPlayer();
    void setStoneClient(int x, int y);
private:
    bool debug_mode;
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
    void NetNewField(vector<vector<int> >);
    void NetWinVector(QVector<int>);
    void NetGameStart();
    void NetPlayersNames(vector<string>);
    void NetAktPlayer(int);

};

#endif // CLIENT_H
