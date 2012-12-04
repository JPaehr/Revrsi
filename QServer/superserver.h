#ifndef SUPERSERVER_H
#define SUPERSERVER_H
#include"server.h"
#include "Logic.h"
#include <QObject>
#include <vector>

using namespace std;

class SuperServer : public QObject
{
    Q_OBJECT
public:
    SuperServer(int breite, int hoehe, int Spieler);


    Server *uServer1;
    Server *uServer2;
    Server *uServer3;
    Server *uServer4;
public slots:
    void setStoneControl(int);
signals:
    void setStone(int);
private:
    int width, heigth, players;


    Logic *logic;

    vector<vector<int> > fields;
    string StringSpielstand();
    void SpielStandaktSenden();

};

#endif // SUPERSERVER_H
