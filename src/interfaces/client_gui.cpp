#include "client_gui.h"
#include "ui_client_gui.h"

client_gui::client_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client_gui){
    ui->setupUi(this);
    this->playerCounter = 0;
    this->clientCounter = 0;
    connect(ui->connect_button,SIGNAL(clicked()),this,SLOT(startClient()));
    connect(this,SIGNAL(addPlayerS(std::vector<std::string>)),this,SLOT(addPlayer(std::vector<std::string>)));
    connect(ui->spielername_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(getPlayerNameOnChange(QString)));
}

client_gui::~client_gui(){
    delete ui;
}

QVector<QString> client_gui::getAllNames(){
    QVector<QString> names;
    for(int i = 1; i<= this->playerCounter; i++){
        names.push_back(QString::fromStdString(this->NetPlayerNames[i][0]));
    }
    return names;
}

QString client_gui::getPlayerName(){
    this->ownName = ui->spielername_lineEdit->text();
    return this->ownName;
}

void client_gui::getPlayerNameOnChange(QString ownName){
    this->ownName = ownName;
    //emit sendOwnName(this->ownName);
}

void client_gui::startClient(){
    if(ui->spielername_lineEdit->text() == QString("")){
        QMessageBox warning;
        warning.setWindowTitle("Fehler");
        warning.setText("KeinSpielername angegeben.");
        warning.setStandardButtons(QMessageBox::Ok);
        warning.exec();
    }
    else{
        emit send_startClient();
    }
}

void client_gui::NetAddPlayer(std::string pl){
    //this->NetPlayerNames.push_back(pl);
    this->clientCounter++;
    QString a;
    a = QString::fromStdString(pl);
    if(this->playerCounter == 1){
        ui->player1->setText(a);
    }
    else if(this->clientCounter == 2){
        ui->player2->setText(a);
    }
    else if(this->clientCounter == 3){
        ui->player3->setText(a);
    }
    else if(this->clientCounter == 4){
        ui->player4->setText(a);
    }
    //emit addPlayerS(pl);
}

void client_gui::addPlayer(std::vector<std::string> player){
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

