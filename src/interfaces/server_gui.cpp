#include "server_gui.h"
#include "ui_server_gui.h"

server_gui::server_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::server_gui)
{
    ui->setupUi(this);
    connect(ui->startServer_button,SIGNAL(clicked()),this,SLOT(setupServer()));

}

server_gui::~server_gui(){
    delete ui;
}

QVector<int> server_gui::getGameValues()
{    int pnum;
     this->height = ui->hoehe_spinbox->value();
     this->width = ui->breite_spinbox->value();
     if(ui->two_player_btn->isChecked()){
         pnum = 2;
     }
     else if(ui->three_player_btn->isChecked()){
         pnum = 3;
     }
     else{
         pnum = 4;
     }
     QVector<int> r;
     r.push_back(ui->breite_spinbox->value());
     r.push_back(ui->hoehe_spinbox->value());
     r.push_back(pnum);
     ui->breite_spinbox->setDisabled(true);
     ui->hoehe_spinbox->setDisabled(true);
     ui->two_player_btn->setCheckable(false);
     ui->three_player_btn->setCheckable(false);
     ui->four_player_btn->setCheckable(false);
     return r;
}

void server_gui::setupServer(){
    emit startServer();
}

