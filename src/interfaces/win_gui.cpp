#include "win_gui.h"
#include "ui_win_gui.h"
#include <QDebug>
#define out qDebug()

win_gui::win_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::win_gui)
{
    ui->setupUi(this);
}

win_gui::~win_gui(){
    delete ui;
}


void win_gui::win_slot(QVector<int> in_vector){
    win_vector = in_vector;
    if(win_vector.size() == 3){
        ui->platz3->hide();
        ui->dritter->hide();
        ui->platz4->hide();
        ui->vierter->hide();
        ui->platz1->move(92,90);
        ui->platz2->move(290,90);
        ui->erster->move(40,160);
        ui->zweiter->move(240,160);
        ui->crown->move(30,80);
    }
    else if(win_vector.size() == 4){
        ui->platz4->hide();
        ui->vierter->hide();
        ui->platz1->move(182,20);
        ui->platz2->move(60,140);
        ui->platz3->move(303,140);
        ui->crown->move(120,10);
        ui->erster->move(130,90);
        ui->zweiter->move(10,200);
        ui->dritter->move(250,200);
    }
    else if(win_vector.size() == 5){
        ui->platz1->move(120,10);
        ui->platz2->move(182,22);
        ui->platz3->move(51,110);
        ui->platz4->move(322,110);
        ui->crown->move(182,200);
        ui->erster->move(130,90);
        ui->zweiter->move(160,131);
        ui->dritter->move(270,160);
        ui->vierter->move(131,260);
    }
}
