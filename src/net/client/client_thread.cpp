#include "client_thread.h"

client_thread::client_thread(QObject *parent, client_gui *ClientInterface ) : QThread(parent){
        this->serverMode = false;
        this->firstfielddrawn = false;
        this->ClientInterface = ClientInterface;
        connect(this->ClientInterface,SIGNAL(disconnect()),this,SLOT(NetPlayerDisconnect()));
}

client_thread::client_thread(QObject *parent, server_gui *ServerInterface, string ip, QString Name) : QThread(parent){
    this->ip = ip;
    this->Name = Name;
    this->serverMode = true;
    this->ServerInterface = ServerInterface;
}

client_thread::~client_thread(){
}

vector<vector<int> > client_thread::getFields(){
    return this->fields;
}

void client_thread::run(){
    if(!serverMode){
        this->myClient = new Client(this->ClientInterface->getIP());
    }
    else{
        this->myClient = new Client(this->ip);
    }
    this->CreateConnectsSuccessful = false;
    emit NetCreateConnects();
    while(!this->CreateConnectsSuccessful){QApplication::processEvents();}
    this->myClient->start();

    while(1){
        if(this->myClient->runtime >= 5){
            if(!serverMode){
                emit this->NetClientSendName(this->ClientInterface->getPlayerName());
                break;
            }
            else{
                emit this->NetClientSendName(this->Name);
                break;
            }
        }
        QApplication::processEvents();
    }

    sleep(1);

    //senden
    //while(this->message == "NONE"){

    //}
    //while(1){
        //this->myClient->senden("");
    //}
    while(1){
        if(!serverMode){
            if(this->ClientInterface->finClientInterface){
                this->terminateClient();
            }
        }
        QApplication::processEvents();
    }
    //this->exec();
}

void client_thread::setCreateConnectsState(bool value){
    this->CreateConnectsSuccessful = value;
}

void client_thread::terminateClient(){
    this->ClientInterface->setClientUnLocked();
    this->ClientInterface->close();
    this->myClient->terminate();
    this->myClient->wait();
    this->myClient->~Client();
    this->terminate();
    this->wait();
    this->~client_thread();
}

void client_thread::NetFieldChange(vector<vector<int> > in_field_vector){
    this->field_vector = in_field_vector;
}

void client_thread::NetGameStart(){
    cout << "ClientThread SLOT:" << "NetGameStart" << endl;
    if(!serverMode){
        this->playerNames = this->ClientInterface->getAllNames();
        emit NetCloseClientInterface();
    }
    else{
        this->ServerInterface->getAllNames();
        this->ServerInterface->hide();
    }
    emit NetNewGame();
}

void client_thread::NetFieldClicked(int x, int y){
    cout << "ClientThread SLOT:\t" << "NetFieldClicked" << endl;
    this->myClient->setStoneClient(x,y);
}

void client_thread::NetSendName(QString ownName){
    cout << "ClientThread SLOT:\t" << "Case 222 NetSendName" << endl;
    this->myClient->sendNameClient(ownName);
}

void client_thread::NetGetID(int id){
    this->ID = id;
    cout << "ClientThread:\t" << "ID bekommen: " << this->ID << endl;
}

void client_thread::NetGetNewField(){
    cout << "ClientThread SLOT:\t" << "NetGetNewField" << endl;
    if(!this->firstfielddrawn){
        this->fields = this->myClient->getFields();
        this->firstfielddrawn = true;
        emit NetNewFields();
    }
    else{
        emit NetNewAniVec(this->myClient->VecAnimation);
    }
}

void client_thread::NetPlayerDisconnect(){
    stringstream sstrID;
    sstrID << this->ID;
    cout << "ClientThread\t Case 201 senden" << endl;
    this->myClient->senden("201," + sstrID.str() + ",");
    this->myClient->disconnect();
    this->myClient->terminate();
    this->myClient->wait();
    this->myClient->~Client();
    this->terminate();
    this->wait();
    this->~client_thread();
}
