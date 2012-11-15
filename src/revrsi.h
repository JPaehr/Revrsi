#ifndef REVRSI_H
#define REVRSI_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "FieldItem.h"
#include "TokenItem.h"
#include "Logic.h"
#include "settings.h"

namespace Ui {
class Revrsi;
}

class Revrsi : public QMainWindow
{

    Q_OBJECT
public:
    explicit Revrsi(QWidget *parent = 0);
    ~Revrsi();
private:
    int width;
    int height;
    int player_num;
    int player_act;
    double scale;
    Ui::Revrsi *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QVector<FieldItem *> fields;
    QVector<TokenItem *> tokens;
    vector<vector<int> > old_array;
    vector<vector<int> > new_array;

    void setupBackground(int x, int y);
    void setupToken(int x, int y,  int player);
    void set_scale(double scale = 50);
    void placeTokens(Logic *logic);
    void init_placeTokens(Logic *logic);

    void new_game(Logic *logic);
};

#endif // REVRSI_H
