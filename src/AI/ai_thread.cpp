#include "ai_thread.h"
#include <iostream>

using namespace std;

AI_Thread::AI_Thread(QObject *parent, int version, int player) : QThread(parent){
    this->player = player;
    this->KIversion = version;
    this->stop = false;
    this->animation_finished = true;
    this->firstRun = true;

    if(version == 1){
        this->AI = new AI_CODE(this->KIversion);
    }
}

void AI_Thread::delaytime(int height){
    this->height = height;
}

void AI_Thread::run(){
    while(1){
        while(!this->animation_finished){
            QApplication::processEvents();
        }
        while(this->stop){QApplication::processEvents();}
        QApplication::processEvents();
        if(this->aktPlayer == player){
            int x = -1,y = -1;

            this->AI->CODE(this->field, &x, &y, player);
            if(x == -1 && y == -1){
                this->terminate();
                this->wait();
                this->~AI_Thread();
            }
            emit AIClicked(x,y);
        }
        if(!this->firstRun){
            this->animation_finished = false;
        }
        else{
            this->firstRun = false;
        }
        //this->msleep(200);
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

void AI_Thread::setAnimationFinished(){
    this->animation_finished = false;
}
