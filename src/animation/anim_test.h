#ifndef ANIM_TEST_H
#define ANIM_TEST_H

#include <QtGui>
#include "../player.h"
#include <QAnimationGroup>

class anim_test: public QThread
{    
    Q_OBJECT
public:
    anim_test(QObject *parent, QVector<player *> p_list);
    void run();
    int akt_player;

signals:
    void animChange();

private:
    QVector<player *> pp;
};

#endif // ANIM_TEST_H
