#ifndef SUPERSERVER_H
#define SUPERSERVER_H
#include"subServer.h"
#include "../../Logic.h"
#include <QObject>
#include <vector>

using namespace std;

class Server : public QObject
{
    Q_OBJECT
public:
    Server(int breite, int hoehe, int Spieler);
    void globalSend(std::string msg);

    subServer *uServer1;
    subServer *uServer2;
    subServer *uServer3;
    subServer *uServer4;
public slots:
    void setStoneControl(int, int, int);
    void NetSendNewClient(QString, int);
    void NetSendSpielstandSL();
    void NetSetServerConnectedSL(int);

private:
    int width, heigth, players;

    bool uServer1Connected,uServer2Connected,uServer3Connected,uServer4Connected;

    Logic *logic;

    vector<vector<int> > fields;
    string StringSpielstand();
    void SpielStandaktSenden();
    vector<string> AllClients;

};

#endif // SUPERSERVER_H
