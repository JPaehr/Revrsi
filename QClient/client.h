#ifndef CLIENT_H
#define CLIENT_H
#include <QThread>
#include "socket.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Client: public QThread{
public:
    Client(string host);
    void ausfuehren();
    void run();
    int width = 0;
    int height = 0;
private:
    string spielerName;
    int feldDa = 0;
    int id, players;
    vector<vector<int> > fields;
    vector<string> explode(const string& str, char delimiter);
    Socket client;
    std::string werte = "";
};

#endif // CLIENT_H
