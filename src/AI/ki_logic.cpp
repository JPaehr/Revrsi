#include "ki_logic.h"


ki_logic::ki_logic(int breite, int hoehe, int anzSpieler, vector<vector<int> > startVector, int spielerNr)
    :Logic(breite, hoehe, anzSpieler){

    this->setWidth(breite);
    this->setHeight(hoehe);
    this->setPlayers(anzSpieler);
    this->nr = spielerNr;
}

void ki_logic::vectorUpdate(vector<vector<int> > aktVector){
    this->setFields(aktVector);
}
vector<int> ki_logic::KiXY(){
    vector<int> gedrehteSteine;
    vector<vector<int> > altesFeld = this->getFields();

    int steineAktuell = 0;
    for(int i = 0; i < this->getHeight(); i++){
        for(int j = 0; j < this->getWidth(); j++){
            if(getFields()[i][j] == this->getAktPlayer()){
                steineAktuell++;
            }
        }
    }

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
        }
    }

    int indexMeisteDrehungen;

    for(unsigned int i = 0; i < gedrehteSteine.size(); i+=3){
        if(i == 0){
            indexMeisteDrehungen = gedrehteSteine[i];
        }
        else if(gedrehteSteine[i] < gedrehteSteine[indexMeisteDrehungen]){
            indexMeisteDrehungen = i;
        }
    }

    vector<int> rueckgabe;
    rueckgabe.push_back(gedrehteSteine[indexMeisteDrehungen+1]);
    rueckgabe.push_back(gedrehteSteine[indexMeisteDrehungen+2]);

    return rueckgabe;
}
