#include "ki_logic.h"
#include <iostream>

using namespace std;

ki_logic::ki_logic()
    :Logic(3,3,3){

    this->setWidth(3);
    this->setHeight(3);
    this->setPlayers(3);
    //cout << "Breite: " << breite << endl;
    //cout << "Hoehe: " << hoehe << endl;
}

void ki_logic::vectorUpdate(vector<vector<int> > aktVector){
    this->width = aktVector[0].size();
    this->height = aktVector.size();
    this->setFields(aktVector);
}
void ki_logic::setNr(int nr){
    this->nr = nr;
}

vector<int> ki_logic::KiXY(){

    cout << "SpielerKi " << this->nr << endl;
    for(int i = 0; i < this->getHeight(); i++){
        for(int j = 0; j < this->getWidth(); j++){
            cout << this->fields[i][j] << " ";
        }
        cout << endl;
    }

    vector<int> gedrehteSteine;
    vector<vector<int> > altesFeld = this->getFields();

    cout << "alles super bis hier" << endl;

    int steineAktuell = 0;

    for(int i = 0; i < this->getHeight(); i++){
        for(int j = 0; j < this->getWidth(); j++){
            if(getFields()[i][j] == this->nr){
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

    int indexMeisteDrehungen = 0;

    for(unsigned i = 0; i < gedrehteSteine.size(); i+=3){
        if(i == 0){
            cout << "Index ist 0" << endl;
            indexMeisteDrehungen = 0;
        }
        else if(gedrehteSteine[i] < gedrehteSteine[indexMeisteDrehungen]){
            cout << "gedrehte Steine: " << gedrehteSteine[i] << endl;
            indexMeisteDrehungen = i;
        }
    }

    cout << "Index Meiste drehungen: " << indexMeisteDrehungen << endl;

    cout << "Hier kurz vor rueckgabe" << endl;
    vector<int> rueckgabe;

    if(gedrehteSteine.size() == 0){
        return rueckgabe;
    }

    rueckgabe.push_back(gedrehteSteine[indexMeisteDrehungen+1]);
    rueckgabe.push_back(gedrehteSteine[indexMeisteDrehungen+2]);
    cout << "Ki x " << rueckgabe[0] << endl;
    cout << "Ki y " << rueckgabe[1] << endl;

    return rueckgabe;
}
