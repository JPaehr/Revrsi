#ifndef AI_THREAD_H
#define AI_THREAD_H

#include <QtGui>
#include "ai_code.h"

using namespace std;

class AI_Thread : public QThread
{
    Q_OBJECT
public:
    int id;
    AI_Thread(QObject *parent, int version, int player);
    void kiPause(bool *kiPause);
    void run();
    virtual ~AI_Thread();
    bool stop;
signals:
    void AIClicked(int,int);
public slots:
    void setField(vector<vector<int> >);
    void setAktPlayer(int);
private:
    bool *pause;
    vector<vector<int> > field;
    int aktPlayer;
    int KIversion;
    int player;
    AI_CODE *AI;
};

#endif // AI_THREAD_H
