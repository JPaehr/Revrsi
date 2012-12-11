#ifndef SERVER_H
#define SERVER_H
#include <QThread>
#include "../socket.h"
#include <string>
#include <vector>
#include "../../Logic.h"
//#include <QObject>
#include <QtGui>

using namespace std;
class subServer : public QThread
{
    Q_OBJECT
signals:
    void setStone(int, int, int);
    void NetServerNewClient(string, int);

public:
    subServer(QObject *parent, string port, int breite, int hoehe, int anzSpieler);
    void run();
    void senden(string nachrict);
    vector<vector<int> > getFelder();
    string StringSpielstand();

    vector<vector<int> > fields;

    void initServer();
    bool connected;
    int id;

private:
    Logic *ThreadLogic;
    vector<std::string> explode(const string& str, char delimiter);
    int width, height, aktPlayer;
    int breite, hoehe;
    string port;
    Socket sock1, sock2;
    string empfang;
    string name;
    string implode( const string &glue, const vector<string> &pieces );
    vector<vector<string> > players;

};

#endif // SERVER_H
