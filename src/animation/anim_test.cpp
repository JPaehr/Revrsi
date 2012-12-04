#include "anim_test.h"
#define out qDebug()

anim_test::anim_test(QObject *parent) : QThread(parent){
    //this->pp = p_list;
}

void anim_test::run(){
    out << "im in thread";
        sleep(2);
        emit delayedStart();
}
