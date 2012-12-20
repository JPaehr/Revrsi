#ifndef CLIENT_THREAD_H
#define CLIENT_THREAD_H

#include <QtGui>
#include <iostream>
#include "client.h"
#include <QObject>
#include "../../interfaces/client_gui.h"
#include "../../interfaces/server_gui.h"
#include <sstream>

using namespace std;

class client_thread : public QThread
{
    Q_OBJECT
public:
    client_thread(QObject *parent, client_gui *ClientInterface);
    client_thread(QObject *parent, server_gui *ServerInterface = 0, string ip = "", QString Name = "");
    ~client_thread();
    Client *myClient;
    vector<vector<int> > getFields();
    void run();
    void setCreateConnectsState(bool value);
    void terminateClient();
signals:
    void NetCreateConnects();
    void NetNewGame();
    void NetNewFields();
    void NetClientSendName(QString);
    void NetCloseClientInterface();

public slots:
    void NetFieldChange(std::vector<std::vector<int> >);
    void NetGameStart();
    void NetFieldClicked(int, int);
    void NetSendName(QString);
    void NetGetID(int);
    void NetGetNewField();
    void NetPlayerDisconnect();

private:
    client_gui *ClientInterface;
    server_gui *ServerInterface;
    vector<vector<int> > field_vector;
    QVector<QString> playerNames;
    int ID;
    vector<vector<int> > fields;
    bool CreateConnectsSuccessful;
    string ip;
    QString Name;
    bool serverMode;
};

#endif // CLIENT_THREAD_H