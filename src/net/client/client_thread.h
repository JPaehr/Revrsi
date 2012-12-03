#ifndef CLIENT_THREAD_H
#define CLIENT_THREAD_H

#include <QtGui>
#include <iostream>
//#include "client.h"
#include <QObject>

using namespace std;

class client_thread : public QThread
{
    Q_OBJECT
public:
    client_thread(QObject *parent);
    void run();
};

#endif // CLIENT_THREAD_H
