#ifndef AI_THREAD_H
#define AI_THREAD_H

#include <QtGui>

using namespace std;

class AI_Thread : public QThread
{
    Q_OBJECT
public:
    AI_Thread(QObject *parent, int version, int player);
    void run();
signals:
    void AIClicked(int,int);
public slots:
    void setField(vector<vector<int> >);
    void setAktPlayer(int);
private:
    vector<vector<int> > field;
    int aktPlayer;
    int KIversion;
    int player;
};

#endif // AI_THREAD_H
