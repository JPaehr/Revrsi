#ifndef SERVER_H
#define SERVER_H
#include <QThread>
#include "socket.h"
#include <string>
#include <vector>
#include "Logic.h"
//#include <QObject>

using namespace std;
class Server : public QThread
{

public:
    Server(string port, int breite, int hoehe, int anzSpieler);
    void run();
    void senden(string nachrict);
    vector<vector<int> > getFelder();
    string StringSpielstand();

    vector<vector<int> > fields;
private:
    Logic *ThreadLogic;
    vector<std::string> explode(const string& str, char delimiter);
    int width, height, aktPlayer;
    int breite, hoehe;
    Socket sock1, sock2;
    string empfang;
    string implode( const string &glue, const vector<string> &pieces );

signals:
    void setStone(int value);

};

#endif // SERVER_H
