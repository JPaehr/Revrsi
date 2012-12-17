#include "server_thread.h"
#define out qDebug()

server_thread::server_thread(QObject *parent, server_gui *serverInterface) : QThread(parent){
    this->serverInterface = serverInterface;
    this->br = false;
    connect(this->serverInterface,SIGNAL(stopServer()),this,SLOT(NetStopServer()));

}

void server_thread::run(){

    out << "serverthread";

    //Server *meinServer = new Server("55313", this->serverInterface->getGameValues()[0], this->serverInterface->getGameValues()[1], this->serverInterface->getGameValues()[2]);

    this->breite = this->serverInterface->getWidth();
    this->hoehe  = this->serverInterface->getHeight();
    this->Spieler= this->serverInterface->getPNum();

    QString PlayerName = this->serverInterface->getName();


    //int breite = 8, hoehe = 8, Spieler = 2;

    this->meinServer = new Server(breite, hoehe, Spieler);
    connect(this->meinServer,SIGNAL(NetNewServer(int)),this,SLOT(NetJumpToConnection(int)));
    QApplication::processEvents();

    this->loop = 1;
    while(1){
        if(this->loop == 1){
            this->br = false;
            int temp_loop = this->loop;
            bool rbreak = false;
            if(!this->meinServer->uServer1Connected){
                this->meinServer->uServer1->start();
                while(!this->meinServer->uServer1->connected){
                    QApplication::processEvents();
                }
            }
            if(this->loop == temp_loop && !rbreak){
                this->loop = 2;
            }
        }

        if(this->loop == 2 && this->meinServer->uServer1Connected){
            this->br = false;
            int temp_loop = this->loop;
            bool rbreak = false;
            if(!this->meinServer->uServer2Connected){
                this->meinServer->uServer2->start();
                this->loop = 2;
                while(!this->meinServer->uServer2->connected){
                    QApplication::processEvents();
                    if(!this->meinServer->uServer1Connected){
                        rbreak = true;
                        this->br = true;
                        this->meinServer->NetDestroyServer(2);
                        this->loop = 1;
                        break;
                    }
                }
            }
            if(this->loop == temp_loop && !rbreak){
                this->loop = 3;
            }
        }
        if(this->loop == 3 && this->meinServer->uServer2Connected){
            int temp_loop = this->loop;
            bool rbreak = false;
            if(Spieler > 2){
                if(!this->meinServer->uServer3Connected){
                    this->meinServer->uServer3->start();
                    this->loop = 3;
                    while(!this->meinServer->uServer3->connected){
                        QApplication::processEvents();
                        if(!this->meinServer->uServer2Connected){
                            rbreak = true;
                            this->br = true;
                            this->meinServer->NetDestroyServer(3);
                            this->loop = 2;
                            break;
                        }
                    }
                }
            }
            if(this->loop == temp_loop && !rbreak){
                this->loop = 4;
            }
        }
        if(this->loop == 4 && this->meinServer->uServer3Connected){
            int temp_loop = this->loop;
            bool rbreak = false;
            if(Spieler >= 4){
                if(!this->meinServer->uServer4Connected){
                    this->meinServer->uServer4->start();
                    this->loop = 4;
                    while(!this->meinServer->uServer4->connected){
                        QApplication::processEvents();
                        if(!this->meinServer->uServer3Connected){
                            rbreak = true;
                            this->br = true;
                            this->meinServer->NetDestroyServer(4);
                            this->loop = 3;
                            break;
                        }
                    }
                }
            }
            if(this->loop == temp_loop && !rbreak){
                this->loop = 0;
            }
        }
        QApplication::processEvents();
    }
}

server_thread::~server_thread(){
}

void server_thread::NetServerStartGame(){
    this->meinServer->globalSend("400,");
}

void server_thread::NetJumpToConnection(int loop){
    if(!br){
        this->loop = loop;
    }
}

void server_thread::NetStopServer(){
    this->serverInterface->setUIUnLocked();
    cout << "ServerThread:\tstopping Server..." << endl;
    if(this->meinServer->uServer1->isRunning()){
        cout << "ServerThread:\tTerminate uServer1" << endl;
        this->meinServer->uServer1->disconnect();
        this->meinServer->uServer1->terminate();
        this->meinServer->uServer1->wait();
        this->meinServer->uServer1->~subServer();
    }
    if(this->meinServer->uServer2->isRunning()){
        cout << "ServerThread:\tTerminate uServer2" << endl;
        this->meinServer->uServer1->disconnect();
        this->meinServer->uServer1->terminate();
        this->meinServer->uServer1->wait();
        this->meinServer->uServer1->~subServer();
    }
    if(this->Spieler >= 3){
        if(this->meinServer->uServer3->isRunning()){
            cout << "ServerThread:\tTerminate uServer3" << endl;
            this->meinServer->uServer1->disconnect();
            this->meinServer->uServer1->terminate();
            this->meinServer->uServer1->wait();
            this->meinServer->uServer1->~subServer();
        }
    }
    if(this->Spieler >= 4){
        if(this->meinServer->uServer4->isRunning()){
            cout << "ServerThread:\tTerminate uServer4" << endl;
            this->meinServer->uServer1->disconnect();
            this->meinServer->uServer1->terminate();
            this->meinServer->uServer1->wait();
            this->meinServer->uServer1->~subServer();
        }
    }
    cout << "ServerThread:\tTerminate MeSelf" << endl;
    this->terminate();
    this->wait();
    this->~server_thread();
}


