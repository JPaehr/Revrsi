#ifndef SUPERSERVER_H
#define SUPERSERVER_H
#include"subServer.h"
#include "Logic.h"
#include <QObject>
#include <vector>

using namespace std;

class Server : public QObject
{
    Q_OBJECT
public:
    Server(int breite, int hoehe, int Spieler);


    subServer *uServer1;
    subServer *uServer2;
    subServer *uServer3;
    subServer *uServer4;
public slots:
    void setStoneControl(int, int, int);

private:
    int width, heigth, players;


    Logic *logic;

    vector<vector<int> > fields;
    string StringSpielstand();
    void SpielStandaktSenden();

};

#endif // SUPERSERVER_H
