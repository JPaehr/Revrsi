#include "ki_logic.h"
#include <iostream>

using namespace std;

ki_logic::ki_logic(int breite, int hoehe, int anzSpieler, vector<vector<int> > startVector, int spielerNr)
    :Logic(breite, hoehe, anzSpieler){

    this->setWidth(breite);
    this->setHeight(hoehe);
    this->setPlayers(anzSpieler);
    this->nr = spielerNr;
    this->fields = startVector;
}

void ki_logic::vectorUpdate(vector<vector<int> > aktVector){
    this->setFields(aktVector);
}
vector<int> ki_logic::KiXY(){
    vector<int> gedrehteSteine;
    vector<vector<int> > altesFeld = this->getFields();

    cout << "alles super bis hier" << endl;

    int steineAktuell = 0;

    for(int i = 0; i < this->getHeight(); i++){
        for(int j = 0; j < this->getWidth(); j++){
            if(getFields()[i][j] == this->getAktPlayer()){
                steineAktuell++;
            }
        }
    }

    cout << "Aktuelle Steine " << steineAktuell << endl;
    int steineAlt = steineAktuell;
    for(int i = 0; i < this->getHeight(); i++){
        for(int j = 0; j < this->getHeight(); j++){
            setField(j, i);



            for(int k = 0; k < this->getHeight(); k++){
                for(int l = 0; l < this->getWidth(); l++){
                    if(this->nr == getFields()[k][l]){
                        steineAktuell--;
                    }
                }
            }
            if(steineAktuell < 0){
                //anzahl in negativ
                gedrehteSteine.push_back(steineAktuell);
                //xwert
                gedrehteSteine.push_back(j);
                //ywert
                gedrehteSteine.push_back(i);
            }

            vectorUpdate(altesFeld);
            this->setAktPlayer(this->nr);
            steineAktuell = steineAlt;
        }
    }
    cout << "eigentlich alles vorbei" << endl;

    int indexMeisteDrehungen;

    for(int i = 0; i < gedrehteSteine.size(); i+=3){
        if(i == 0){
            cout << "Index ist 0" << endl;
            indexMeisteDrehungen = 0;
        }
        else if(gedrehteSteine[i] < gedrehteSteine[indexMeisteDrehungen]){
            cout << "gedrehte Steine: " << gedrehteSteine[i] << endl;
            indexMeisteDrehungen = i;
        }
    }

    cout << "Hier kurz vor rueckgabe" << endl;
    vector<int> rueckgabe;
    rueckgabe.push_back(gedrehteSteine[indexMeisteDrehungen+1]);
    rueckgabe.push_back(gedrehteSteine[indexMeisteDrehungen+2]);


    return rueckgabe;
}
