#include "ai_thread.h"

AI_Thread::AI_Thread(QObject *parent, int version, int player) : QThread(parent){
    this->player = player;
    this->KIversion = version;
    this->stop = false;

    if(version == 1){
        this->AI = new AI_CODE(this->KIversion);
    }
}
void AI_Thread::kiPause(bool *kiPause){
    this->pause = kiPause;
}

void AI_Thread::run(){
    if(*this->pause == false){
        msleep(1500);
        *this->pause = true;
    }

    while(1){
        while(this->stop){QApplication::processEvents();}
        QApplication::processEvents();
        if(this->aktPlayer == player){
            int x = -1,y = -1;


            this->AI->CODE(this->field, &x, &y, player);
            if(x == -1 && y == -1){
                qDebug() << "Terminate AI" << endl;
                this->terminate();
                this->wait();
                this->~AI_Thread();
            }
            emit AIClicked(x,y);
        }
        this->msleep(100);
    }
}

AI_Thread::~AI_Thread(){
}

void AI_Thread::setField(vector<vector<int> > rfield){
    this->field = rfield;
}

void AI_Thread::setAktPlayer(int aP){
    this->aktPlayer = aP;
}
