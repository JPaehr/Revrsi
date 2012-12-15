#include "ai_thread.h"

AI_Thread::AI_Thread(QObject *parent, int version, int player) : QThread(parent){
    this->player = player;
    this->KIversion = version;
}

void AI_Thread::run(){
    while(1){
        QApplication::processEvents();
        if(this->aktPlayer == player){
            int x,y;

            /*******************************
             **        KI Code Here       **
             **    -assign x and y        **
             **/


            x= 2;
            y= 2;

            /********  KI Code End  *********/

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
