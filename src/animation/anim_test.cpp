#include "anim_test.h"

anim_test::anim_test(QObject *parent, QVector<player *> p_list) : QThread(parent){
    this->pp = p_list;
}

void anim_test::run(){
    for(;;){
        sleep(3);
        //emit animChange();
    }


}
