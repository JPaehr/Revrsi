#include "client_thread.h"

client_thread::client_thread(QObject *parent, client_gui *ClientInterface) : QThread(parent){
    this->ClientInterface = ClientInterface;
}

void client_thread::run(){
    this->myClient = new Client("localhost", false);

    //recv in Thread
    this->myClient->start();



    sleep(1);

    //senden
    //while(this->message == "NONE"){

    //}
    this->myClient->senden("");
}

void client_thread::NetFieldChange(vector<vector<int> > in_field_vector){
    this->field_vector = in_field_vector;

}

void client_thread::NetGameStart(){
}

void client_thread::NetFieldClicked(){
}
