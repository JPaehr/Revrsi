#include "anim_test.h"

anim_test::anim_test(QObject *parent) : QThread(parent){
    //this->pp = p_list;
}

void anim_test::run(){
    emit delayedStart();

    for(int i = 0; i< this->t_group.size(); i++){
        this->t_group[i]->start();
        msleep(5);
    }
}

void anim_test::setTimerGroup(QVector<QTimeLine *> t_group){
    this->t_group = t_group;
}
