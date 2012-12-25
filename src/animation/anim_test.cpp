#include "anim_test.h"
#define out qDebug()

anim_test::anim_test(QObject *parent) : QThread(parent){
    //this->pp = p_list;
}

void anim_test::run(){
    out << "im in thread";
        msleep(500);
        emit delayedStart();

        for(int i = 0; i< this->t_group.size(); i++){
            this->t_group[i]->start();
            msleep(5);
        }
}

void anim_test::setTimerGroup(QVector<QTimeLine *> t_group){
    for(int i = 0; i < t_group.size(); i++){
        this->t_group.push_back(t_group[i]);
    }
}
