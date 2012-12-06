#ifndef CLIENT_THREAD_H
#define CLIENT_THREAD_H

#include <QtGui>
#include <iostream>
#include "client.h"
#include <QObject>
#include "../../interfaces/client_gui.h"

using namespace std;

class client_thread : public QThread
{
    Q_OBJECT
public:
    client_thread(QObject *parent, client_gui *ClientInterface);
    Client *myClient;
    void run();
signals:
    void NetCreateConnects();
    void NetNewGame();
public slots:
    void NetFieldChange(std::vector<std::vector<int> >);
    void NetGameStart();
    void NetFieldClicked();
private:
    client_gui *ClientInterface;
    vector<vector<int> > field_vector;
};

#endif // CLIENT_THREAD_H
