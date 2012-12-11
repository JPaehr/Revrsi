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
    vector<vector<int> > getFields();
    void run();
    void setCreateConnectsState(bool value);
signals:
    void NetCreateConnects();
    void NetNewGame();
    void NetNewFields();
    void NetClientSendName(QString);

public slots:
    void NetFieldChange(std::vector<std::vector<int> >);
    void NetGameStart();
    void NetFieldClicked(int, int);
    void NetSendName(QString);
    void NetGetID(int);
    void NetGetNewField();

private:
    client_gui *ClientInterface;
    vector<vector<int> > field_vector;
    QVector<QString> playerNames;
    int ID;
    vector<vector<int> > fields;
    bool CreateConnectsSuccessful;
};

#endif // CLIENT_THREAD_H
