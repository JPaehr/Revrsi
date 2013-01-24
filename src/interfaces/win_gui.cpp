#include "win_gui.h"
#include "ui_win_gui.h"
#include <QDebug>
#define out qDebug()
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
    cout << "INVector" << endl;
    for(int i = 0; i < in_vector.size(); i++){
        cout << in_vector[i] << endl;
    }
    cout << "in names" << endl;
    std::string name = "";
    for(int i = 0; i < in_names.size(); i++){
        name = in_names[i].toStdString();
        cout << name << endl;
    }
    win_vector = in_vector;
    player_names = in_names;


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
            cout << "drittgross: "<< drittgross << endl;
            cout << "Das i dazu " << i << endl;
        }
    }
    for(int i = 1; i < this->win_vector.size(); i++){
        if(this->win_vector[i] == drittgross){
            platzDrei.push_back(i);
        }
    }
    if(platzDrei.size() > 0){
        cout << "platz 3 reingepusht " << endl;
        for(int i = 0; i <platzDrei.size(); i++){
            cout << "eintraege " << platzDrei[i] << endl;
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

    //zu versteckende Teile finden
    int zaehler = 0;
    for(int i = 0; i < platzierung.size(); i++){
        for(int j = 0; j < platzierung[i].size(); j++){
            zaehler++;
            cout << "I " << i;
            cout << "j " << j;
        }
    }
    if(zaehler == 2){
        cout << "Spielercontroll 2" << endl;
        ui->platz3->hide();
        ui->platz4->hide();
        ui->dritter->hide();
        ui->vierter->hide();
    }
    if(zaehler == 3){
        cout << "Spielercontorll 3" << endl;
        ui->platz4->hide();
        ui->vierter->hide();
    }
    if(platzierung[0].size() > 1){
        ui->crown->hide();
    }
    int platz = 1;
    for(int i = 0; i < platzierung.size(); i++){
        cout << "platz " << platz << endl;
        if(platz == 4){
            ui->vierter->setText(in_names[platzierung[i][0]-1]+"\n"+QString::number(in_vector[platzierung[i][0]]) +" Punkte");
            ui->vierter->move(130, 255);
            ui->platz4->move(130, 240);
            platz++;
        }
        if(platz == 3){
            if(platzierung[i].size() > 1){
                cout << "platz 3 ist doppelt" << endl;
                ui->dritter->setText(in_names[platzierung[i][0]-1] + "\n"+QString::number(in_vector[platzierung[i][0]]) +" Punkte");
                ui->dritter->move(195, 175);
                ui->platz3->move(195, 160);

                ui->vierter->setText(in_names[platzierung[i][1]-1] +"\n"+QString::number(in_vector[platzierung[i][1]]) +" Punkte");
                ui->vierter->move(260, 175);
                ui->platz4->setText("2");
                ui->platz4->move(260, 160);
                platz+=2;
            }
            else{
                cout << "Platz 3 einzel" << endl;
                ui->dritter->setText(in_names[platzierung[i][0]-1]+"\n"+QString::number(in_vector[platzierung[i][0]]) +" Punkte");
                ui->dritter->move(230, 175);
                ui->platz3->move(230, 160);
                platz++;
            }
        }
        if(platz == 2){

            cout << "schleife bei platz2 <<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

            if(platzierung[1].size() > 1){
                cout << "platz 2 ist doppelt" << endl;
                ui->zweiter->setText(in_names[platzierung[i][0]-1] + "\n"+QString::number(in_vector[platzierung[i][0]]) +" Punkte");
                ui->zweiter->move(65, 175);
                ui->platz2->move(65, 160);

                ui->dritter->setText(in_names[platzierung[i][1]-1] +"\n"+QString::number(in_vector[platzierung[i][1]]) +" Punkte");
                ui->dritter->move(200, 175);
                ui->platz3->setText("2");
                ui->platz3->move(200, 160);
                platz+=2;
            }
            else{
                cout << "Platz 2 einzel" << endl;
                //cout << "winvec " << in_vector[platzierung[1][0]];
                //cout << platzierung[1][0] << endl;
                ui->zweiter->setText(in_names[platzierung[i][0]-1] + "\n" + QString::number(in_vector[platzierung[i][0]]) +" Punkte");
                ui->zweiter->move(65, 175);
                ui->platz2->move(65, 160);
                platz++;
            }
        }
        if(platz == 1){
            if(platzierung[0].size() > 1){
                cout << "platz 1 ist doppelt" << endl;
                ui->erster->move(65, 105);
                ui->erster->setText(in_names[platzierung[i][0]-1] +"\n"+ QString::number(in_vector[platzierung[i][0]])+" Punkte");
                ui->platz1->move(65, 90);
                ui->crown->hide();

                ui->zweiter->move(230, 105);
                ui->zweiter->setText(in_names[platzierung[i][1]-1] + "\n" + QString::number(in_vector[platzierung[i][1]])+" Punkte");
                ui->platz2->setText("1");
                ui->platz2->move(230, 90);
                platz+=2;
            }
            else{
                //cout << "winvec" << in_vector[platzierung[0][0]] << endl;

                ui->erster->setText(in_names[platzierung[i][0]-1]+"\n"+QString::number(in_vector[platzierung[i][0]])+ " Punkte");
                //ui->platz1pkt->setText(QString::number(in_vector[platzierung[0][0]])+ " Punkte");
                //ui->platz1pkt->move(130, 80);
                ui->erster->move(130, 105);
                ui->platz1->move(130, 90);
                platz+=1;
                cout << "schleife1 hat einen nach oben gezaehlt" << endl;
            }
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
    /*
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
    */
}
