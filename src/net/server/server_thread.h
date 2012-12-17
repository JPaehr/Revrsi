#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <QtGui>
#include "../socket.h"
#include <iostream>
#include "server.h"
#include <vector>
#include <string>
#include <QObject>
#include "../../interfaces/server_gui.h"
#include "server.h"

using namespace std;

class server_thread : public QThread
{
    Q_OBJECT
public:
    server_thread(QObject *parent, server_gui *serverInterface);
    void run();
    ~server_thread();
public slots:
    void NetServerStartGame();
    void NetJumpToConnection(int);
    void NetStopServer();

private:
    Server *meinServer;
    QString message;
    server_gui *serverInterface;
    int loop;
    bool br;
    int breite,hoehe,Spieler;
};

#endif // SERVER_THREAD_H
