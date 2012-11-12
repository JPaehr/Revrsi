#ifndef REVRSI_H
#define REVRSI_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "FieldItem.h"
#include "TokenItem.h"

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
    double scale;
    Ui::Revrsi *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    void setupBackground(int x, int y, QGraphicsScene *scene, QVector<FieldItem *> *fields);
    void setToken(int x, int y,  int player, double scale, QVector<FieldItem *> fields, QGraphicsScene *scene);
    void set_scale(double scale = 50);
};

#endif // REVRSI_H
