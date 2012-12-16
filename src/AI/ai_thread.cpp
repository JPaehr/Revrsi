#include "ai_thread.h"

AI_Thread::AI_Thread(QObject *parent, int version, int player) : QThread(parent){
    this->player = player;
    this->KIversion = version;

    if(version == 1){
        this->AI = new AI_CODE(this->KIversion);
    }
}

void AI_Thread::run(){
    while(1){
        QApplication::processEvents();
        if(this->aktPlayer == player){
            int x = -1,y = -1;

            this->AI->CODE(this->field, &x, &y);

            emit AIClicked(x,y);
        }
        this->msleep(100);
    }
}

void AI_Thread::setField(vector<vector<int> > rfield){
    this->field = rfield;
}

void AI_Thread::setAktPlayer(int aP){
    this->aktPlayer = aP;
}
