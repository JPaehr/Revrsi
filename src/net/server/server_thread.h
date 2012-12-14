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
public slots:
    void NetServerStartGame();
    void NetJumpToConnection(int);

private:
    Server *meinServer;
    QString message;
    server_gui *serverInterface;
    int loop;
};

#endif // SERVER_THREAD_H
