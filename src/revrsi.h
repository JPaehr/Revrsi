#ifndef REVRSI_H
#define REVRSI_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "FieldItem.h"
#include "TokenItem.h"
#include "Logic.h"
#include "new_game_settings.h"
#include "server_gui.h"

namespace Ui {
class Revrsi;
}

class Revrsi : public QMainWindow
{
    Q_OBJECT

public:
    explicit Revrsi(QWidget *parent = 0);
    ~Revrsi();

public slots:
    void test_slot();
    void server_gui_slot();
    void field_clicked_slot(int, int);

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
    QTimer                  *timer;
    QVector<FieldItem *>    fields;
    QVector<TokenItem *>    tokens;
    server_gui              *serverInterface;
    vector<vector<int> >    old_array;
    vector<vector<int> >    new_array;

    void change_token(int x, int y,  int player);
    void init_placeTokens(Logic *logic);
    void new_game();
    void placeTokens(Logic *logic);
    void set_scale(double scale = 50);
    void setupBackground(int x, int y);
    void setupToken(int x, int y,  int player);

    void animtest(FieldItem *item);
};

#endif // REVRSI_H
