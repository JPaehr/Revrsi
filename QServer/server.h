#ifndef SERVER_H
#define SERVER_H
#include <QThread>
#include "socket.h"
#include <string>
#include <vector>

using namespace std;
class Server : public QThread
{
public:
    Server(string port, int breite, int hoehe);
    void run();
    void ausfuehren(string nachrict);
    vector<vector<int> > getFelder();
    string StringSpielstand();

    vector<vector<int> > fields;
private:
    vector<std::string> explode(const string& str, char delimiter);
    int width, height;
    int breite, hoehe;
    Socket sock1, sock2;
    string empfang;
    string implode( const string &glue, const vector<string> &pieces );

};

#endif // SERVER_H
