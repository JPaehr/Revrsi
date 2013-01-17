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
#include "net/server/server_thread.h"
#include "net/client/client_thread.h"
#include "AI/ai_thread.h"
#include "interfaces/ai_settings.h"

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
    void delayedStart();
    void win(QVector<int>, QVector<QString>);

    //Network
    void emitAktPlayer(int);
    void emitField(vector<vector<int> >);
    void NetFieldClickedTransmit(int, int);

public slots:
    //Window show slots
    void new_game_slot();
    void server_gui_slot();
    void field_clicked_slot(int, int);
    void client_gui_slot();

    //Toolbar item slots
    void step_left();
    void step_right();
    void step_top();
    void step_down();
    void zoom_in();
    void zoom_out();

    void switchOpacityWay();

    void warpStart();
    void AIClickSlot(int,int);

    //Netzwerk
    void NetCreateConnectsSL();
    void NetNewFieldSL();
    void NetNewAniVecSL(vector<int>);
    void NetNewGame();
    void NetSetGameValues(int, int, int);
    void NetUpdatePlayer(int);
    void NetUpdateWinVector(QVector<int>);
    void runClient(QString ip = "", QString Name = "");
    void runServer();
    void setNetModeEnabled();
    void setNetModeDisabled();
    void set_proceed_newGame_true();
    void stopServerSL();

private:

    bool    FieldBackSet;
    bool    firstRun;
    bool    direction;

    bool    clientInit,serverInit;
    bool    NetMode;
    bool    NetGameStart;
    bool    NewGame;
    bool    serverMode;
    bool    skipTurn;

    double  scale;
    double  sceneOffset_scale;

    int     animatedPlayer;
    int     height;
    int     width;
    int     player_act;
    int     player_num;
    int     sceneOffset_x;
    int     sceneOffset_y;

    AI_settings             *ais;
    client_gui              *clientInterface;
    client_thread           *ClientThread;
    new_game_settings       *ngs;
    Logic                   *logic;
    Ui::Revrsi              *ui;
    QGraphicsScene          *scene;
    QGraphicsScene          *frame_scene;
    QPropertyAnimation      *anim;
    QSequentialAnimationGroup *initSanim;
    QTimer                  *timer;

    QVector<QString>        playerNames;
    QVector<AI_Thread *>    ai_list;
    QVector<FieldItem *>    fields;
    QVector<TokenItem *>    tokens;
    QVector<player *>       p_fields;
    QVector<QTimeLine *>    t_group;

    server_gui              *serverInterface;
    server_thread           *ServerThread;
    TokenItem               *TokenContainer;

    vector<int>             aninnn;
    vector<vector<int> >    old_array;
    vector<vector<int> >    new_array;
    vector<int>             win_vector;

    win_gui                 *winInterface;

    void addPlayersToList();
    void change_token(int x, int y,  int player);
    void change_tokenII();
    void change_token_pixmap(TokenItem *token);
    void createAIs();
    void init_placeTokens();
    void new_game();
    void runPlayerFieldAnimation();
    void set_scale(double scale = 50);
    void setupBackground(int x, int y);
    void setupBackgroundTheme();
    void setupFieldBack();
    void setupToken(int x, int y,  int player);

    void closeEvent(QCloseEvent *);
};

#endif // REVRSI_H
