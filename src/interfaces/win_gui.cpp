#include "win_gui.h"
#include "ui_win_gui.h"
#include <QDebug>
#define out qDebug()
#include <iostream>

using namespace std;

win_gui::win_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::win_gui)
{
    ui->setupUi(this);
}

win_gui::~win_gui(){
    delete ui;
}


void win_gui::win_slot(QVector<int> in_vector, QVector<QString> in_names){
    win_vector = in_vector;
    player_names = in_names;

    for(int i = 0; i < this->win_vector.size(); i++){
        cout << "WinVector kommt" << endl;
        cout << this->win_vector[i] << endl;
    }

    //anzahl der Plaetze berechnen+
    vector<int> punkte;
    for(int i = 1; i < this->win_vector.size(); i++){
        punkte.push_back(this->win_vector[i]);
    }
    int punktegleichstand = 0, anzPlaetze, anzSpieler;
    for(int i = 0; i < punkte.size(); i++){
        for(int j = 0; j < punkte.size(); j++){
            if(punkte[i] == punkte[j] && i != j){
                punktegleichstand++;
            }
        }
    }
    anzSpieler = this->win_vector.size()-1;
    anzPlaetze = anzSpieler-punktegleichstand;


    //zuordnung Platz mit punktzahl
        //hoechstepunktzahl finden
    int gross = 0, zweitgross = 0, drittgross = 0;
    for(int i = 1; i < this->win_vector.size(); i++){
        if(gross < this->win_vector[i]){
            gross = this->win_vector[i];
        }
    }
    vector<vector<int> > platzierung;
    //alle erste plaetze finden

    vector<int> platzEins, platzZwei, platzDrei, platzvier;
    for(int i = 1; i < this->win_vector.size(); i++){
        if(this->win_vector[i] == gross){
            platzEins.push_back(i);
        }
    }
    platzierung.push_back(platzEins);

    //platz 2 finden
        //zweithoechstepunktzahl finden

    for(int i = 1; i < this->win_vector.size(); i++){
        if(this->win_vector[i] > zweitgross && gross != this->win_vector[i]){
            zweitgross = this->win_vector[i];
        }
    }
    for(int i = 1; i < this->win_vector.size(); i++){
        if(this->win_vector[i] == zweitgross){
            platzZwei.push_back(i);
        }
    }
    if(platzZwei.size() > 0){
        platzierung.push_back(platzZwei);
    }

    //platz 3 finden
        //drittgroesste pktzahl finden
    for(int i = 1; i < this->win_vector.size(); i++){
        if(this->win_vector[i] > drittgross && this->win_vector[i] != gross && this->win_vector[i] != zweitgross){
            drittgross = this->win_vector[i];
        }
    }
    for(int i = 1; i < this->win_vector.size(); i++){
        if(this->win_vector[i] == drittgross){
            platzDrei.push_back(i);
        }
    }
    if(platzDrei.size() > 0){
        platzierung.push_back(platzDrei);
    }

    //platz vier
    for(int i = 1; i < this->win_vector.size(); i++){
        if(this->win_vector[i] != gross && this->win_vector[i] != zweitgross && this->win_vector[i] != drittgross){
            platzvier.push_back(this->win_vector[i]);

        }
    }
    if(platzvier.size() > 0){
        platzierung.push_back(platzvier);
    }

    for(int i = 0; i < platzierung.size(); i++){
        if(i == 0){
            cout << "Platz 1:" << endl;
        }
        if(i == 1){
            cout << "Platz 2: " << endl;
        }
        if(i == 2){
            cout << "Platz 3:" << endl;
        }
        if(i == 3){
            cout << "Platz 4: " << endl;
        }
        for(int j = 0; j < platzierung[i].size(); j++){
            cout << platzierung[i][j] << endl;
        }
    }

    /*RückgabeCodes für gleiche Punkzahlen zwischen Spielern:
     *1u2 = -2
     *1u3 = -3
     *1u4 = -4
     *2u3 = -5
     *2u4 = -6
     *3u4 = -7
     *1u2u3 = -8
     *1u2u4 = -9
     *1u3u4 = -10
     *2u3u4 = -11
     *1u2u3u4 = -12
    */

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
        if(win_vector[0] == -2){
            ui->erster->setText(player_names[0]);
            ui->zweiter->setText(player_names[1]);
            ui->crown->setVisible(false);
        }
        if(win_vector[0] == 1){
            ui->erster->setText(player_names[0]);
            ui->zweiter->setText(player_names[1]);
        }
        else if(win_vector[0] == 2){
            ui->erster->setText(player_names[1]);
            ui->zweiter->setText(player_names[0]);
        }
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
        if(win_vector[0] == -2){
            if(win_vector[3] < win_vector[1]){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
            else{
                ui->erster->setText(player_names[2]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[1]);
                ui->crown->setVisible(false);
            }
        }
        else if(win_vector[0] == -3){
            if(win_vector[2] < win_vector[1]){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[1]);
                ui->crown->setVisible(false);
            }
            else{
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
        }
        else if(win_vector[0] == -5){
            if(win_vector[1] < win_vector[2]){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[0]);
                ui->crown->setVisible(false);
            }
            else{
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
        }
    }
    else if(win_vector.size() == 5){
        ui->platz4->move(180,190);
        ui->vierter->move(130,250);
        ui->platz1->move(182,20);
        ui->platz2->move(60,140);
        ui->platz3->move(303,140);
        ui->crown->move(120,10);
        ui->erster->move(130,90);
        ui->zweiter->move(10,200);
        ui->dritter->move(250,200);

        //1u2,3,4
        if(win_vector[0] == -2){
            if(win_vector[1] > (win_vector[3] > win_vector[4])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[1] > (win_vector[4] > win_vector[3])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[3] > (win_vector[1] > win_vector[4])){
                ui->erster->setText(player_names[2]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[3] > (win_vector[4] > win_vector[1])){
                ui->erster->setText(player_names[2]);
                ui->zweiter->setText(player_names[3]);
                ui->dritter->setText(player_names[0]);
                ui->vierter->setText(player_names[1]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[4] > (win_vector[3] > win_vector[1])){
                ui->erster->setText(player_names[3]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[0]);
                ui->vierter->setText(player_names[1]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[4] > (win_vector[1] > win_vector[3])){
                ui->erster->setText(player_names[3]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
        }
        //1u3,2,4
        else if(win_vector[0] == -3){
            if(win_vector[1] > (win_vector[2] > win_vector[4])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[1] > (win_vector[4] > win_vector[2])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[1]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[2] > (win_vector[1] > win_vector[4])){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[2] > (win_vector[4] > win_vector[1])){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[3]);
                ui->dritter->setText(player_names[0]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[4] > (win_vector[1] > win_vector[2])){
                ui->erster->setText(player_names[3]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[1]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[4] > (win_vector[2] > win_vector[1])){
                ui->erster->setText(player_names[3]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[0]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
        }
        //1u4,2,3
        else if(win_vector[0] == -4){
            if(win_vector[1] > (win_vector[2] > win_vector[3])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[3]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[1] > (win_vector[3] > win_vector[2])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[3]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[1]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[2] > (win_vector[1] > win_vector[3])){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[2] > (win_vector[3] > win_vector[1])){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[0]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[3] > (win_vector[1] > win_vector[2])){
                ui->erster->setText(player_names[2]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[1]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[3] > (win_vector[2] > win_vector[1])){
                ui->erster->setText(player_names[2]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[0]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
        }
        //2u3,1,4
        else if(win_vector[0] == -5){
            if(win_vector[2] > (win_vector[1] > win_vector[4])){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[0]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[2] > (win_vector[4] > win_vector[1])){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[0]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[1] > (win_vector[2] > win_vector[4])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[1] > (win_vector[4] > win_vector[2])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[3]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[4] > (win_vector[2] > win_vector[1])){
                ui->erster->setText(player_names[3]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[0]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[4] > (win_vector[1] > win_vector[2])){
                ui->erster->setText(player_names[3]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
        }
        //2u4,1,3
        else if(win_vector[0] == -6){
            if(win_vector[2] > (win_vector[1] > win_vector[3])){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[3]);
                ui->dritter->setText(player_names[0]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[2] > (win_vector[3] > win_vector[1])){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[3]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[0]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[1] > (win_vector[2] > win_vector[3])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[1] > (win_vector[3] > win_vector[2])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[3] > (win_vector[2] > win_vector[1])){
                ui->erster->setText(player_names[2]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[0]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[3] > (win_vector[1] > win_vector[2])){
                ui->erster->setText(player_names[2]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
        }
        //3u4,1,2
        else if(win_vector[0] == -7){
            if(win_vector[3] > (win_vector[1] > win_vector[2])){
                ui->erster->setText(player_names[2]);
                ui->zweiter->setText(player_names[3]);
                ui->dritter->setText(player_names[0]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[3] > (win_vector[2] > win_vector[1])){
                ui->erster->setText(player_names[2]);
                ui->zweiter->setText(player_names[3]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[0]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[1] > (win_vector[3] > win_vector[2])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[1]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[1] > (win_vector[2] > win_vector[3])){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[2] > (win_vector[3] > win_vector[1])){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[0]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[2] > (win_vector[1] > win_vector[3])){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
        }
        //1u2u3,4
        else if(win_vector[0] == -8){
            if(win_vector[1] > win_vector[4]){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[4] > win_vector[1]){
                ui->erster->setText(player_names[3]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
        }
        //1u2u3,4
        else if(win_vector[0] == -9){
            if(win_vector[1] > win_vector[3]){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[2]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[3] > win_vector[1]){
                ui->erster->setText(player_names[2]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[1]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
        }
        //1u2u3,4
        else if(win_vector[0] == -10){
            if(win_vector[1] > win_vector[2]){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[1]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[2] > win_vector[1]){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[0]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
        }
        //1u2u3,4
        else if(win_vector[0] == -11){
            if(win_vector[2] > win_vector[1]){
                ui->erster->setText(player_names[1]);
                ui->zweiter->setText(player_names[2]);
                ui->dritter->setText(player_names[3]);
                ui->vierter->setText(player_names[0]);
                ui->crown->setVisible(false);
            }
            else if(win_vector[1] > win_vector[2]){
                ui->erster->setText(player_names[0]);
                ui->zweiter->setText(player_names[1]);
                ui->dritter->setText(player_names[2]);
                ui->vierter->setText(player_names[3]);
                ui->crown->setVisible(false);
            }
        }
        //1u2u3u4
        else if(win_vector[0] == -11){
            ui->erster->setText(player_names[0]);
            ui->zweiter->setText(player_names[1]);
            ui->dritter->setText(player_names[2]);
            ui->vierter->setText(player_names[3]);
            ui->crown->setVisible(false);
        }
        else{
            ui->erster->setText(player_names[0]);
            ui->zweiter->setText(player_names[1]);
            ui->dritter->setText(player_names[2]);
            ui->vierter->setText(player_names[3]);
            ui->crown->setVisible(true);
        }
    }
}
