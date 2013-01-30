#include "win_gui.h"
#include "ui_win_gui.h"
#include <iostream>
#include "string"

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

    std::string name = "";
    for(int i = 0; i < in_names.size(); i++){
        name = in_names[i].toStdString();
        //cout << name << endl;
    }
    win_vector = in_vector;
    player_names = in_names;


    //anzahl der Plaetze berechnen+
    vector<int> punkte;
    for(int i = 1; i < this->win_vector.size(); i++){
        punkte.push_back(this->win_vector[i]);
    }
    int punktegleichstand = 0;
    //int anzPlaetze, anzSpieler;
    for(uint i = 0; i < punkte.size(); i++){
        for(uint j = 0; j < punkte.size(); j++){
            if(punkte[i] == punkte[j] && i != j){
                punktegleichstand++;
            }
        }
    }
    //anzSpieler = this->win_vector.size()-1;
    //anzPlaetze = anzSpieler-punktegleichstand;


    //zuordnung Platz mit punktzahl
        //hoechstepunktzahl finden
    int gross = -1, zweitgross = -1, drittgross = -1;
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
            //cout << "drittgross: "<< drittgross << endl;
            //cout << "Das i dazu " << i << endl;
        }
    }
    for(int i = 1; i < this->win_vector.size(); i++){
        if(this->win_vector[i] == drittgross){
            platzDrei.push_back(i);
        }
    }
    if(platzDrei.size() > 0){
        //cout << "platz 3 reingepusht " << endl;
        for(uint i = 0; i <platzDrei.size(); i++){
            //cout << "eintraege " << platzDrei[i] << endl;
        }
        platzierung.push_back(platzDrei);
    }

    //platz vier
    for(int i = 1; i < this->win_vector.size(); i++){
        if((this->win_vector[i] != gross) && (this->win_vector[i] != zweitgross) && (this->win_vector[i] != drittgross)){
            platzvier.push_back(i);

        }
    }
    if(platzvier.size() > 0){
        platzierung.push_back(platzvier);
    }

    vector<int> reihenfolge;
    vector<int> platznr;
    for(uint i = 0; i < platzierung.size(); i++){
        for(uint j = 0; j < platzierung[i].size(); j++){
            reihenfolge.push_back(platzierung[i][j]);
            platznr.push_back(i+1);
        }
    }

    QString wortPunkt;
    if(reihenfolge.size() == 2){
        ui->dritter->hide();
        ui->platz3->hide();
        ui->vierter->hide();
        ui->platz4->hide();
    }
    if(reihenfolge.size() == 3){
        ui->vierter->hide();
        ui->platz4->hide();
    }
    QFont f( "Arial", 30, QFont::Bold);
    for(uint i = 0; i < reihenfolge.size(); i++){
        if(reihenfolge.size() == 2){
            if(i == 0){
                if(platznr[i] != platznr[i+1]){
                    ui->crown->move(15,20);
                }
                if(in_vector[reihenfolge[i]] == 1){
                    wortPunkt = "Punkt";
                }
                else{
                    wortPunkt = "Punkte";
                }
                ui->platz1->setText(QString::number(platznr[i]));
                ui->platz1->setFont(f);
                ui->erster->move(25, 150);
                ui->erster->setText(in_names[reihenfolge[i]-1] +"\n"+ QString::number(in_vector[reihenfolge[i]])+" "+wortPunkt);
                ui->platz1->move(75, 100);
            }
            if(i == 1){
                if(in_vector[reihenfolge[i]] == 1){
                    wortPunkt = "Punkt";
                }
                else{
                    wortPunkt = "Punkte";
                }
                ui->zweiter->move(230, 150);
                ui->platz2->setFont(f);
                ui->zweiter->setText(in_names[reihenfolge[i]-1] +"\n"+ QString::number(in_vector[reihenfolge[i]])+" "+wortPunkt);
                ui->platz2->move(280, 100);
                ui->platz2->setText(QString::number(platznr[i]));


            }
        }
        else{
            if(i == 0){
                if(in_vector[reihenfolge[i]] == 1){
                    wortPunkt = "Punkt";
                }
                else{
                    wortPunkt = "Punkte";
                }
                ui->platz1->setText(QString::number(platznr[i]));
                ui->platz1->setFont(f);
                ui->erster->move(130, 120);
                ui->erster->setText(in_names[reihenfolge[i]-1] +"\n"+ QString::number(in_vector[reihenfolge[i]])+" "+wortPunkt);
                ui->platz1->move(180, 70);
            }
            if(i == 1){
                if(in_vector[reihenfolge[i]] == 1){
                    wortPunkt = "Punkt";
                }
                else{
                    wortPunkt = "Punkte";
                }
                ui->zweiter->move(15, 190);
                ui->platz2->setFont(f);
                ui->zweiter->setText(in_names[reihenfolge[i]-1] +"\n"+ QString::number(in_vector[reihenfolge[i]])+" "+wortPunkt);
                ui->platz2->move(65, 140);
                ui->platz2->setText(QString::number(platznr[i]));
            }
            if(i == 2){
                if(in_vector[reihenfolge[i]] == 1){
                    wortPunkt = "Punkt";
                }
                else{
                    wortPunkt = "Punkte";
                }
                ui->dritter->move(245, 190);
                ui->platz3->setFont(f);
                ui->dritter->setText(in_names[reihenfolge[i]-1] +"\n"+ QString::number(in_vector[reihenfolge[i]])+" "+wortPunkt);
                ui->platz3->setText(QString::number(platznr[i]));
                ui->platz3->move(295, 140);
            }
            if(i == 3){
                if(in_vector[reihenfolge[i]] == 1){
                    wortPunkt = "Punkt";
                }
                else{
                    wortPunkt = "Punkte";
                }
                ui->vierter->move(130, 250);
                ui->platz4->setFont(f);
                ui->vierter->setText(in_names[reihenfolge[i]-1] +"\n"+ QString::number(in_vector[reihenfolge[i]])+" "+wortPunkt);
                ui->platz4->move(180, 200);
                ui->platz4->setText(QString::number(platznr[i]));
            }
        }
    }
}
