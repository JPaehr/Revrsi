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
    return ui->spielername_lineEdit->text();
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
    this->close();
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

void server_gui::setUIUnLocked(){
    ui->breite_spinbox->setDisabled(false);
    ui->hoehe_spinbox->setDisabled(false);
    ui->two_player_btn->setDisabled(false);
    ui->three_player_btn->setDisabled(false);
    ui->four_player_btn->setDisabled(false);
    ui->startServer_button->setDisabled(false);
    ui->stopServer_button->setEnabled(false);
    ui->spielername_lineEdit->setDisabled(false);
}

QVector<QString> server_gui::getAllNames(){
    //cout << "ClientInterface\tgetAllNames()" << endl;
    return this->NetPlayerNames;
}

void server_gui::NetAddPlayerServer(QVector<QString> pl){
    //cout << "ClientInterface\tNetAddPlayer()" << endl;
    for(int i = 0; i<pl.size(); i+=2){
        if(pl[i+1] == "1"){
            ui->player1->setText(pl[i]);
            ui->ID1_label->setText("ID: " + pl[i+1]);
            if(!this->NetPlayerNames.contains(pl[i])){
                this->NetPlayerNames.push_back(pl[i]);
            }
        }
        else if(pl[i+1] == "2"){
            ui->player2->setText(pl[i]);
            ui->ID2_label->setText("ID: " + pl[i+1]);
            if(!this->NetPlayerNames.contains(pl[i])){
                this->NetPlayerNames.push_back(pl[i]);
            }
        }
        else if(pl[i+1] == "3"){
            ui->player3->setText(pl[i]);
            ui->ID3_label->setText("ID: " + pl[i+1]);
            if(!this->NetPlayerNames.contains(pl[i])){
                this->NetPlayerNames.push_back(pl[i]);
            }
        }
        else if(pl[i+1] == "4"){
            ui->player4->setText(pl[i]);
            ui->ID4_label->setText("ID: " + pl[i+1]);
            if(!this->NetPlayerNames.contains(pl[i])){
                this->NetPlayerNames.push_back(pl[i]);
            }
        }
    }
    bool p1 = false ,p2 = false,p3 = false,p4 = false;
    for(int i = 1;i < pl.size(); i+=2 ){
        if(pl[i] == "1"){
            p1 = true;
        }
        if(pl[i] == "2"){
            p2 = true;
        }
        if(pl[i] == "3"){
            p3 = true;
        }
        if(pl[i] == "4"){
            p4 = true;
        }
    }
    if(!p1){
        ui->player1->setText("Leer");
        ui->ID1_label->setText("ID: ");
    }
    if(!p2){
        ui->player2->setText("Leer");
        ui->ID2_label->setText("ID: ");
    }
    if(!p3){
        ui->player3->setText("Leer");
        ui->ID3_label->setText("ID: ");
    }
    if(!p4){
        ui->player4->setText("Leer");
        ui->ID4_label->setText("ID: ");
    }
}

