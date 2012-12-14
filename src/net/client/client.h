#ifndef CLIENT_H
#define CLIENT_H
#include <QThread>
#include "../socket.h"
#include <string>
#include <iostream>
#include <vector>
#include <QVector>
#include <QMetaType>

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
    void sendNameClient(QString ownName);
    vector<vector<int> > getFields();
    int runtime;
    bool disconnectSend;


private:
    bool debug_mode;
    vector<int> winVector;
    string name;
    int id, players;
    bool running;
    vector<vector<int> > fields;
    vector<string> explode(const string& str, char delimiter);
    Socket client;
    int aktPlayer;
    QVector<QString> playersNames;
    string werte;
    int ConnectedClients;

signals:
    void NetNewField();
    void NetWinVector(vector<int>);
    void NetServerWantGameStart();
    void NetPlayersNames(QVector<QString>);
    void NetAktPlayer(int);
    void NetGameValues(int, int, int);
    void NetGotID(int);

};

#endif // CLIENT_H
