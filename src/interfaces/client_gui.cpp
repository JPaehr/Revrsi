#include "client_gui.h"
#include "ui_client_gui.h"
#include <QApplication>
#include <QDebug>
#include <iostream>

client_gui::client_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client_gui){
    ui->setupUi(this);
    this->playerCounter = 0;
    this->clientCounter = 0;
    this->finClientInterface = false;
    connect(ui->close_button,SIGNAL(clicked()),this,SLOT(close()));
    //connect(this,SIGNAL(destroyed()),this,SLOT(cclose()));
    connect(ui->connect_button,SIGNAL(clicked()),this,SLOT(startClient()));
    connect(this,SIGNAL(send_startClient()),this,SLOT(setLockedSL()));
    connect(this,SIGNAL(addPlayerS(std::vector<std::string>)),this,SLOT(addPlayer(std::vector<std::string>)));
    connect(ui->spielername_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(getPlayerNameOnChange(QString)));
}

client_gui::~client_gui(){
    delete ui;
}

QVector<QString> client_gui::getAllNames(){
    cout << "ClientInterface\tgetAllNames()" << endl;
    return this->NetPlayerNames;
}

QString client_gui::getPlayerName(){
    cout << "ClientInterface\tgetPlayerName()" << endl;
    this->ownName = ui->spielername_lineEdit->text();
    return this->ownName;
}

string client_gui::getIP(){
    cout << "ClientInterface\tgetIP()" << endl;
    return ui->serverIP_lineEdit->text().toStdString();
}

void client_gui::setLockedSL(){
    cout << "ClientInterface\tsetLockedSL()" << endl;
    ui->serverIP_lineEdit->setDisabled(true);
    ui->spielername_lineEdit->setDisabled(true);
}

void client_gui::setClientUnLocked(){
    cout << "ClientInterface\tsetClientUnLocked()" << endl;
    ui->serverIP_lineEdit->setDisabled(false);
    ui->spielername_lineEdit->setDisabled(false);
}

void client_gui::closeEvent(QCloseEvent *event){
    //emit disconnect();
    //QApplication->processEvents();
    //event->accept();
    this->finClientInterface = true;
    qDebug() << "testestestestestestestestestestestesest";
    event->accept();
}

//void client_gui::closeEvent(QCloseEvent *){

//}

void client_gui::getPlayerNameOnChange(QString ownName){
    this->ownName = ownName;
    //emit sendOwnName(this->ownName);
}

void client_gui::startClient(){
    if(ui->spielername_lineEdit->text() == QString("")){
        QMessageBox warning;
        warning.setWindowTitle("Fehler");
        warning.setText("Kein Spielername angegeben.");
        warning.setStandardButtons(QMessageBox::Ok);
        warning.exec();
    }
    else if(ui->serverIP_lineEdit->text() == QString("")){
        QMessageBox warning;
        warning.setWindowTitle("Fehler");
        warning.setText("Keine Server IP angegeben.");
        warning.setStandardButtons(QMessageBox::Ok);
        warning.exec();
    }
    else{
        emit send_startClient();
    }
}

void client_gui::NetAddPlayer(QVector<QString> pl){
    cout << "ClientInterface\tNetAddPlayer()" << endl;
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
    //emit addPlayerS(pl);
}

void client_gui::addPlayer(std::vector<std::string> player){
    cout << "ClientInterface\taddPlayer()" << endl;
    this->playerCounter += 1;
    if(this->playerCounter == 1){
        ui->player1->setText(QString::fromStdString(player[0]));
        ui->ID1_label->setText("ID: " + QString::fromStdString(player [1]));
    }
    else if(this->playerCounter == 2){
        ui->player2->setText(QString::fromStdString(player[0]));
        ui->ID2_label->setText("ID: " + QString::fromStdString(player [1]));
    }
    else if(this->playerCounter == 3){
        ui->player3->setText(QString::fromStdString(player[0]));
        ui->ID3_label->setText("ID: " + QString::fromStdString(player [1]));
    }
    else if(this->playerCounter == 4){
        ui->player4->setText(QString::fromStdString(player[0]));
        ui->ID4_label->setText("ID: " + QString::fromStdString(player [1]));
    }
}

