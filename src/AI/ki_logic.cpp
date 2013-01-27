#include "ki_logic.h"
#include <iostream>

using namespace std;

ki_logic::ki_logic()
    :Logic(3,3,3){

    this->setWidth(3);
    this->setHeight(3);
    this->setPlayers(3);
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

    vector<int> gedrehteSteine;
    vector<vector<int> > altesFeld = this->getFields();

    int steineAktuell = 0;

    for(int i = 0; i < this->getHeight(); i++){
        for(int j = 0; j < this->getWidth(); j++){
            if(getFields()[i][j] == this->nr){
                steineAktuell++;
            }
        }
    }

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

    int indexMeisteDrehungen = 0;

    for(unsigned i = 0; i < gedrehteSteine.size(); i+=3){
        if(i == 0){
            indexMeisteDrehungen = 0;
        }
        else if(gedrehteSteine[i] < gedrehteSteine[indexMeisteDrehungen]){
            indexMeisteDrehungen = i;
        }
    }

    //seiten kontrollieren
    for(unsigned i = 0;i < gedrehteSteine.size(); i+=3){
        if((gedrehteSteine[i+1] == 0 || gedrehteSteine[i+1] == this->width-1) && (gedrehteSteine[i+2] == 0 || gedrehteSteine[i+2] == this->height-1) &&
                gedrehteSteine[i] >= (gedrehteSteine[indexMeisteDrehungen])-2){
            indexMeisteDrehungen = i;
        }
    }
    //Ecken
    for(unsigned i = 0;i < gedrehteSteine.size(); i+=3){
        if(((gedrehteSteine[i+1] == 0 && gedrehteSteine[i+2] == 0)
           || (gedrehteSteine[i+1] == this->width-1 && gedrehteSteine[i+2] == this->height-1)
           || (gedrehteSteine[i+1] == this->width-1 || gedrehteSteine[i+2] == 0)
           || (gedrehteSteine[i+1] == 0|| gedrehteSteine[i+2] == this->height-1))
             && (gedrehteSteine[i] >= (gedrehteSteine[indexMeisteDrehungen])-1)){
            indexMeisteDrehungen = i;
        }
    }
    vector<int> rueckgabe;

    if(gedrehteSteine.size() == 0){
        return rueckgabe;
    }

    rueckgabe.push_back(gedrehteSteine[indexMeisteDrehungen+1]);
    rueckgabe.push_back(gedrehteSteine[indexMeisteDrehungen+2]);

    return rueckgabe;
}
