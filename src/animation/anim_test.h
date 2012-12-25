#ifndef ANIM_TEST_H
#define ANIM_TEST_H

#include <QtGui>
#include "../player.h"
#include <QAnimationGroup>

class anim_test: public QThread
{    
    Q_OBJECT
public:
    anim_test(QObject *parent);
    void run();
    int akt_player;
    void setTimerGroup( QVector<QTimeLine *> t_group );

signals:
    void animChange();
    void delayedStart();

private:
    QVector<player *> pp;
    QVector<QTimeLine *> t_group;

};

#endif // ANIM_TEST_H
