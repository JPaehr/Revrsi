#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <QtGui>
#include "socket.h"
#include <iostream>
#include "server.h"
#include <vector>
#include <string>
#include <QObject>

using namespace std;

class server_thread : public QThread
{
    Q_OBJECT
public:
    server_thread(QObject *parent);
    void run();
private:
    Server *meinServer;
    QString message;
};

#endif // SERVER_THREAD_H
