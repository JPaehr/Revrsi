#ifndef REVRSI_H
#define REVRSI_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "FieldItem.h"
#include "TokenItem.h"
#include "Logic.h"
#include "interfaces/new_game_settings.h"
#include "interfaces/server_gui.h"
#include "interfaces/client_gui.h"
#include "interfaces/win_gui.h"
#include "player.h"
#include "animation/anim_test.h"
#include "net/server/server_thread.h"
#include "net/client/client_thread.h"

namespace Ui {
class Revrsi;
}

class Revrsi : public QMainWindow
{
    Q_OBJECT

public:
    explicit Revrsi(QWidget *parent = 0);
    ~Revrsi();

signals:
    void win(QVector<int>, QVector<QString>);
    void delayedStart();

public slots:
    void test_slot();
    void server_gui_slot();
    void field_clicked_slot(int, int);
    void client_gui_slot();

    void step_left();
    void step_right();
    void step_top();
    void step_down();
    void zoom_in();
    void zoom_out();
    void switchOpacityWay();

    void warpStart();

    //Netzwerk
    void runServer();
    void runClient();

    void net_field_clicked(std::vector<std::vector<int> >);

private:
    double                  scale;
    int                     width;
    int                     height;
    int                     player_num;
    int                     player_act;
    new_game_settings       *ngs;
    Logic                   *logic;
    Ui::Revrsi              *ui;
    //QAnimationGroup         Anim;
    QGraphicsScene          *scene;
    QGraphicsScene          *frame_scene;
    QVector<QString>        playerNames;
    QTimer                  *timer;
    QVector<FieldItem *>    fields;
    QVector<TokenItem *>    tokens;
    QVector<player *>       p_fields;
    TokenItem               *TokenContainer;
    client_gui              *clientInterface;
    server_gui              *serverInterface;
    win_gui                 *winInterface;
    vector<vector<int> >    old_array;
    vector<vector<int> >    new_array;
    vector<int>             win_vector;

    QPropertyAnimation *anim;

    int                     sceneOffset_x;
    int                     sceneOffset_y;
    double                  sceneOffset_scale;

    bool                    FieldBackSet;

    bool    direction;
    int animatedPlayer;

    bool firstRun;

    void change_token(int x, int y,  int player);
    void init_placeTokens(Logic *logic);
    void new_game();
    void placeTokens(Logic *logic);
    void set_scale(double scale = 50);
    void setupBackground(int x, int y);
    void setupToken(int x, int y,  int player);
    void addPlayersToList();
    void setupBackgroundTheme();
    void setupFieldBack();

    void runPlayerFieldAnimation();

    anim_test *atest;
    void startThread();


    server_thread *ServerThread;
    client_thread *ClientThread;
//    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
};

#endif // REVRSI_H
