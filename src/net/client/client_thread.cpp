#include "client_thread.h"

client_thread::client_thread(QObject *parent, client_gui *ClientInterface) : QThread(parent){
    this->ClientInterface = ClientInterface;
}

vector<vector<int> > client_thread::getFields(){
    return this->fields;
}

void client_thread::run(){
    this->myClient = new Client("localhost", true);
    emit NetCreateConnects();
    //recv in Thread
    this->myClient->start();



    sleep(1);

    //senden
    //while(this->message == "NONE"){

    //}
    //while(1){
        //this->myClient->senden("");
    //}
    this->exec();
}

void client_thread::NetFieldChange(vector<vector<int> > in_field_vector){
    this->field_vector = in_field_vector;

}

void client_thread::NetGameStart(){
    cout << "ClientThread SLOT:" << "NetGameStart" << endl;
    this->playerNames = this->ClientInterface->getAllNames();
    this->ClientInterface->setVisible(false);
    emit NetNewGame();
}

void client_thread::NetFieldClicked(int x, int y){
    cout << "ClientThread SLOT:" << "NetFieldClicked" << endl;
    this->myClient->setStoneClient(x,y);
}

void client_thread::NetSendName(QString ownName){
    cout << "ClientThread SLOT:" << "NetSendName" << endl;
    this->myClient->sendNameClient(ownName);
}

void client_thread::NetGetID(int id){
    this->ID = id;
    cout << "ClientThread:\t" << "ID bekommen: " << this->ID << endl;
}

void client_thread::NetGetNewField(){
    cout << "ClientThread SLOT:\t" << "NetGetNewField" << endl;
    this->fields = this->myClient->getFields();
    emit NetNewFields();
}
