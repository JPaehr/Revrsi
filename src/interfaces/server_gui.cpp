#include "server_gui.h"
#include "ui_server_gui.h"

server_gui::server_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::server_gui)
{
    ui->setupUi(this);
    connect(ui->startServer_button,SIGNAL(clicked()),this,SLOT(setupServer()));
    connect(ui->starGame_button,SIGNAL(clicked()),this,SLOT(NetSendStartGame()));
    connect(ui->stopServer_button,SIGNAL(clicked()),this,SLOT(terminateServer()));
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

int server_gui::getWidth(){
    return ui->breite_spinbox->value();
}

int server_gui::getHeight(){
    return ui->hoehe_spinbox->value();
}

int server_gui::getPNum(){
    if(ui->two_player_btn->isChecked()){
        return 2;
    }
    else if(ui->three_player_btn->isChecked()){
        return 3;
    }
    else if(ui->four_player_btn->isChecked()){
        return 4;
    }
    else{
        return 2;
    }
}

QString server_gui::getName(){
    return ui->spielername_label->text();
}

void server_gui::setupServer(){
    if(ui->spielername_lineEdit->text() == QString("")){
        QMessageBox warning;
        warning.setWindowTitle("Fehler");
        warning.setText("Kein Spielername angegeben.");
        warning.setStandardButtons(QMessageBox::Ok);
        warning.exec();
        return;
    }
    if(ui->breite_spinbox->value() == 0){
        QMessageBox warning;
        warning.setWindowTitle("Fehler");
        warning.setText("Spielfeldbreite zu klein");
        warning.setStandardButtons(QMessageBox::Ok);
        warning.exec();
        return;
    }
    if(ui->hoehe_spinbox->value() == 0){
        QMessageBox warning;
        warning.setWindowTitle("Fehler");
        warning.setText("Spielfeldbreite zu klein");
        warning.setStandardButtons(QMessageBox::Ok);
        warning.exec();
        return;
    }
    this->setUILocked();
    emit startServer();
    ui->starGame_button->setEnabled(true);
}

void server_gui::NetSendStartGame(){
    emit NetStartGame();
}

void server_gui::terminateServer(){
    emit stopServer();
}

void server_gui::setUILocked(){
    ui->breite_spinbox->setDisabled(true);
    ui->hoehe_spinbox->setDisabled(true);
    ui->two_player_btn->setDisabled(true);
    ui->three_player_btn->setDisabled(true);
    ui->four_player_btn->setDisabled(true);
    ui->startServer_button->setDisabled(true);
    ui->stopServer_button->setEnabled(true);
    ui->spielername_lineEdit->setDisabled(true);
}

