/*
 * Logic.cpp
 *
 *  Created on: 04.11.2012
 *      Author: jpaehr
 */

#include "Logic.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <QDebug>

using namespace std;

Logic::Logic(int width, int height, int players) {
	// TODO Auto-generated constructor stub
	this->players = players;
	this->width = width;
	this->height =height;
	//aktPlayer wird zunaechst immer 1 sein
	this->aktPlayer = 1;
	//Felder mit inhalt 0 sollen nicht belegt sein
	//this->fields[5][5] = {0};
	this->fields.assign(height,vector<int>(width,0));
    this->oldFields = this->fields;
}

//Array als rueckgabewert einer Methode ist in c schwierig->nachsehen wie das geht
vector<vector<int> > Logic::getFields(){
	return this->fields;
}
void Logic::setInitStones(){
    int x = 0;
    int y = 0;
	vector<int> Steine;
	//Fuer 2 Spieler
	if(this->players == 2){
		//ungerades Spielfeld in der Breite abfragen
		if(this->width % 2 == 0){
			x = (this->width / 2) - 1;
		}
		else{
			x = (this->width / 2) - (3/2);
		}

		//ungerades Spielfeld in der Hoehe
		if(this->height % 2 == 0){
			y = this->height / 2 - 1;
		}
		else{
			y = (this->height / 2) - (3/2);
		}
		for(int j = 1; j <= 2;j++){
			Steine.push_back(1);
			Steine.push_back(2);
		}

	}

	//Fuer 3 Spieler
	if(this->players == 3){
		if(this->width % 2 == 0){
			x = (this->width / 2) -2;
		}
		else{
			x = (this->width / 2) - (3/2);
		}
		if(this->height % 2 == 0){
			y = (this->height / 2) - 2;
		}
		else{
			y = (this->height / 2) - (3/2);
		}
		for(int j = 1; j <= 3;j++){
			Steine.push_back(1);
			Steine.push_back(2);
			Steine.push_back(3);
		}
	}

	//Fuer 4 Spieler
	if(this->players == 4){
		if(this->width % 2 == 0){
			x = (this->width / 2) -2;
		}
		else{
			x = (this->width / 2) - (5/2);
		}
		if(this->height % 2 == 0){
			y = (this->height / 2) -2;
		}
		else{
			y = (this->height / 2) -(5/2);
		}
		for(int j = 1; j <= 4; j++){
			Steine.push_back(1);
			Steine.push_back(2);
			Steine.push_back(3);
			Steine.push_back(4);
		}
	}

	//Hier muessen die steine jetzt noch gesetzt werden
	random_shuffle(Steine.begin(), Steine.end());
	int counter = 0;

	for(int breite = 1; breite <= players; breite++){
		for(int hoehe = 1; hoehe <= players; hoehe++){
			this->fields[y+hoehe-1][x+breite-1] = Steine[counter];
			counter++;
		}
	}

    this->oldFields = this->fields;
	/*
	// testfeld fuer den beweis, dass die farbe tauscht, wenn eine nicht setzen kann
	this->fields[1][2] = 1;
	this->fields[2][2] = 2;
	this->fields[1][1] = 1;
	this->fields[2][1] = 2;
	 */
}
void Logic::turnStones(int x, int y, int richtung, int anzahl){
	switch (richtung){
	case 0:
		for(int i = 1; i <= anzahl; i++){
			this->fields[y-i][x+i] = this->aktPlayer;
		}
		break;
	case 1:
		for(int i = 1; i <= anzahl; i++){
			this->fields[y-i][x] = this->aktPlayer;
		}
		break;
	case 2:
		for(int i = 1; i <= anzahl; i++){
			this->fields[y-i][x-i] = this->aktPlayer;
		}
		break;
	case 3:
		for(int i = 1; i <= anzahl; i++){
			this->fields[y][x-i] = this->aktPlayer;
		}
		break;
	case 4:
		for(int i = 1; i <= anzahl; i++){
			this->fields[y+i][x-i] = this->aktPlayer;
		}
		break;
	case 5:
		for(int i = 1; i <= anzahl; i++){
			this->fields[y+i][x] = this->aktPlayer;
		}
		break;
	case 6:
		for(int i = 1; i <= anzahl; i++){
			this->fields[y+i][x+i] = this->aktPlayer;
		}
		break;
	case 7:
		for(int i = 1; i <= anzahl; i++){
			this->fields[y][x+i] = this->aktPlayer;
		}
		break;
	default:;
	break;
	}
}
vector<int> Logic::sternSteine(int x, int y){
	int richtungen[8] = {0};

	for(int i = 1; i <= this->height; i++){
		for(int j = 1; j <= this->width; j++){
			//nach obenrechts
			if(y-i >= 0 && x+j <= this->width-1 && j == i && richtungen[0] == 0){
				if(this->fields[y-i][x+j] == 0){
					richtungen[0] = -1;
				}
				else{
					if(this->fields[y-i][x+j] == this->aktPlayer){
						richtungen[0] = j;
					}
				}
			}
			//nach oben
			if(y-i >= 0 && richtungen[1] == 0){
				if(this->fields[y-i][x] == 0){
					richtungen[1] = -1;
				}
				else{
					if(this->fields[y-i][x] == this->aktPlayer){
						richtungen[1] = i;
					}
				}
			}
			//nach obenlink
			if(y-i >= 0 && x-j >= 0 && j == i && richtungen[2] == 0){
				if(this->fields[y-i][x-j] == 0){
					richtungen[2] = -1;
				}
				else{
					if(this->fields[y-i][x-j] == this->aktPlayer && this->fields[y-i][x-j] != 0){
						richtungen[2] = j;
					}
				}
			}
			//nach links
			if(x-j >= 0 && richtungen[3] == 0){
				if(this->fields[y][x-j] == 0){
					richtungen[3] = -1;
				}
				else{
					if(this->fields[y][x-j] == this->aktPlayer && this->fields[y][x-j] != 0){
						richtungen[3] = j;
					}
				}
			}

			//nach untenlinks
			if(y+i <= this->height-1 && x-j >= 0 && j == i && richtungen[4] == 0){
				if(this->fields[y+i][x-j] == 0){
					richtungen[4] = -1;
				}
				else{
					if(this->fields[y+i][x-j] == this->aktPlayer && this->fields[y+i][x-j] != 0){
						richtungen[4] = j;
					}
					//richtungen[4] = j;
				}
			}
			//nach unten
			if(y+i <= this->height-1 && richtungen[5] == 0){
				if(this->fields[y+i][x] == 0){
					richtungen[5] = -1;
				}
				else{
					if(this->fields[y+i][x] == this->aktPlayer && this->fields[y+i][x] != 0){
						richtungen[5] = i;
					}
					//richtungen[5] = i;
				}
			}
			//nach untenrechts
			if(y+i <= this->height-1 && x+j <= this->width-1 && j == i && richtungen[6] == 0){
				if(this->fields[y+i][x+j] == 0){
					richtungen[6] = -1;
				}
				else{
					if(this->fields[y+i][x+j] == this->aktPlayer && this->fields[y+i][x+j] != 0){
						richtungen[6] = j;
					}
					//richtungen[6] = j;
				}
			}
			//nach rechts
			if(x+j <= this->width-1 && richtungen[7] == 0){
				if(this->fields[y][x+j] == 0){
					richtungen[7] = -1;
				}
				else{
					if(this->fields[y][x+j] == this->aktPlayer && this->fields[y][x+j] != 0){
						richtungen[7] = j;
					}
					//richtungen[7] = j;
				}
			}
		}
	}
	vector<int> richtungenVec;
	for(int z = 0; z <= 7; z++){
		richtungenVec.push_back(richtungen[z]);
	}
	return richtungenVec;
}
bool Logic::validation(int x, int y){
	//ist ander Position schon ein stein
	if(this->fields[y][x] == 0){

		//umliegende steine kontrollieren
		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++){
				//wenn i und j beide null muss ausgelassen werden

				if(y+i >= 0 && y+i <= this->height-1 && x+j >= 0 && x+j <= this->width-1 && this->fields[y+i][x+j] != 0){
					//zusatzregel -> drehen kontollieren

					/*
					int punkte = 0;
					for(int zeilen = 0; zeilen < this->height; zeilen++){
						for(int spalten = 0; spalten < this->width; spalten++){
							if(this->fields[zeilen][spalten] == this->aktPlayer){
								punkte++;
							}
						}
					}
					*/
					this->fields[y][x] = this->aktPlayer;
					vector<int> gedrehte = sternSteine(x, y);
					for(int v = 0; v < 8; v++){
						if(gedrehte[v] > 1){
							this->fields[y][x] = 0;
                            //cout << "Das feld sollte gehen " << x << " " << y << endl;
							return true;
						}
					}
					this->fields[y][x] = 0;
				}
			}
		}
	}

	return false;
}
bool Logic::setField(int x, int y){
    this->oldFields = this->fields;

	if(this->validation(x, y)){
		//y und x verdreht, weil y fuer zeilen steht und x fuer breite
		this->fields[y][x] = this->aktPlayer;

		//richtungen legt fest ob in der linie ein gleicher stein gefunden wurde
		// begin oben rechts, also auf eine geraden der steigung 1

		for(int k = 1; k <= 8; k++){
			turnStones(x, y, k-1, sternSteine(x,y)[k-1]);
		}

		//neuer Spieler wird gesetzt
		this->aktPlayer = (this->aktPlayer % this->players) +1;

		int put = 0;
		int durchlauf = 0;

		while(put == 0 && durchlauf < 5){
            //cout << "duchlauf 1";
			put = 0;
			for(int h = 0; h < this->height; h++){
				for(int b = 0; b < this->width; b++){
					if(validation(b,h)){
						put++;
					}
				}
			}
			if(put < 1){
                //cout << "War im put";
				this->aktPlayer = (this->aktPlayer % this->players) + 1;
			}
			durchlauf++;
		}
        //geaenderte Steine finden

        //alte Werte loeschen
        this->aniStonesInZaehlerRichtung.clear();
        this->aniStonesStern.clear();

        //aniStonesInZaehlerRichtung
        for(int i = 0; i < this->height; i++){
            for(int j = 0; j < this->width; j++){
                if(this->fields[i][j] != this->oldFields[i][j]){
                    //cout << "Neues Feld bei x: " <<  j << " und y: " << i << " " << this->fields[i][j] << endl;
                    //cout << "Altes Feld bei x: " << j << " und y: " << i << " " << this->oldFields[i][j] << endl;
                    this->aniStonesInZaehlerRichtung.push_back(j);
                    this->aniStonesInZaehlerRichtung.push_back(i);
                }
            }
        }

        //aniStonesStern
        int distanceFinden = 0;
        if(this->height > this->width){
            distanceFinden = this->height;
        }
        else{
            distanceFinden = this->width;
        }

        for(int distance = 0; distance < distanceFinden+1; distance++){

            for(int i = 0; i < this->height; i++){
                for(int j = 0; j < this->width; j++){
                    if((this->fields[i][j] != this->oldFields[i][j]) && (getDistance(x, y, j, i) == distance) && (this->oldFields[i][j] != (-1))){
                        //cout << "Distanz: " << distance << endl;
                        //cout << "Neues Feld bei x: " <<  j << " und y: " << i << " " << this->fields[i][j] << endl;
                        //cout << "Altes Feld bei x: " << j << " und y: " << i << " " << this->oldFields[i][j] << endl;
                        this->oldFields[i][j] = -1;
                        this->aniStonesStern.push_back(j);
                        this->aniStonesStern.push_back(i);
                    }
                }
            }
            //cout << "letzter eintrag im Stern: " << this->aniStonesStern[this->aniStonesStern.size()-1] << endl;
            if(this->aniStonesStern[this->aniStonesStern.size()-1] != -10){
                this->aniStonesStern.push_back(-10);
            }
        }

        /*
        for(int i = 0; i < this->aniStonesStern.size(); i++){

            if(this->aniStonesStern[i] == -10){
                cout << "-10" << endl;
            }
            else{
                 cout << " " << this->aniStonesStern[i];
            }
        }
        */


        return true;
    }//validation Ende
    return false;
}
int Logic::getDistance(int xSource, int ySource, int xdest, int ydest){
    int xdiff = xSource - xdest;
    int ydiff = ySource - ydest;
    if(xdiff < 0){
        xdiff = xdiff * (-1);
    }
    if(ydiff < 0){
        ydiff = ydiff * (-1);
    }
    if(xdiff > ydiff){
        return xdiff;
    }
    else{
        return ydiff;
    }

}


vector<int> Logic::getAniStones(int aniArt){
    //-1 fuer Stern
    //-2 fuer stumpfes vorgehen in reihe
    switch(aniArt){
        case -1:
            return this->aniStonesStern;
            break;
        case -2:
            return this->aniStonesInZaehlerRichtung;
            break;
        default:
        break;
            //return new vector<int>;
    }
    return this->aniStonesInZaehlerRichtung;
}

vector<int> Logic::win(){
	vector<int> sieger;
	for(int anz = 0; anz <= this->players; anz++){
		sieger.push_back(0);
	}
	for(int k = 1; k <= this->players; k++){
		for(int i = 0; i <= this->height-1; i++){
			for(int j = 0; j <= this->width-1; j++){
				if(this->fields[i][j] == k){
					sieger[k]++;
				}
			}
		}
	}
	//cout << "win ausgefuehrt";
	sieger[0] = -1;

    int felder = (this->height*this->width) ;
	int besetzt = 0;
    for(int i = 0; i <= this->height-1; i++){
        for(int j = 0; j <= this->width-1; j++){
			if(this->fields[i][j] != 0){
				besetzt++;
			}
		}
	}

//	int spieler = this->aktPlayer;
	int moeglicheZuege[this->players];
	for(int i = 0; i < this->players; i++){
		moeglicheZuege[i] = 0;
	}
	for(int player = 0; player < this->players; player++){
		for(int i = 0; i < this->height; i++){
			for(int j = 0; j < this->width; j++){
				if(validation(j, i)){
					moeglicheZuege[player]++;
				}
			}
		}
	}
	int ende = 0;
	int zuege = 0;
	for(int i = 0; i < this->players; i++){
		zuege = zuege + moeglicheZuege[i];
		cout << moeglicheZuege[i] << " ";
	}

	if(zuege == 0){
		ende = 1;
        //cout << "Winende " << ende;
	}
	else{
        //cout << "anzMoeglicher Zuege: " << zuege << endl;
	}


    if(felder == besetzt || ende == 1){

        vector<int> equal_players;
        //for(int i = 1;i<=sieger.size();i++){verivector.push_back(sieger[i]);}
        int winner = 0;
		for(int s = 1; s <= this->players; s++){
			if(sieger[s] > sieger[0]){
                sieger[0] = sieger[s];
                winner = s;
			}
		}
        sieger[0] = winner;
        //erster ausdruck der For schleife "int i = 1, size = sieger.size()" aus dem grund, da sonst ständig eine int uint comparison warnung vom compiler kommt. ist außerdem weniger rechenintensiv
        for(int i = 1, size = sieger.size(); i < size;i++){
            if(sieger[sieger[0]] == sieger[i] && sieger[0] != i){
                equal_players.push_back(i);
            }
            else if(sieger[0] == i){
                equal_players.push_back(i);
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
        if(equal_players.size() == 2){
            if(equal_players[0] == 1 && equal_players[1] == 2){
                sieger[0] = -2;
            }
            else if(equal_players[0] == 1 && equal_players[1] == 3){
                sieger[0] = -3;
            }
            else if(equal_players[0] == 1 && equal_players[1] == 4){
                sieger[0] = -4;
            }
            else if(equal_players[0] == 2 && equal_players[1] == 3){
                sieger[0] = -5;
            }
            else if(equal_players[0] == 2 && equal_players[1] == 4){
                sieger[0] = -6;
            }
            else if(equal_players[0] == 3 && equal_players[1] == 4){
                sieger[0] = -7;
            }
        }
        else if(equal_players.size() == 3){
            if(equal_players[0] == 1 && equal_players[1] == 2 && equal_players[2] == 3){
                sieger[0] = -8;
            }
            else if(equal_players[0] == 1 && equal_players[1] == 2 && equal_players[2] == 4){
                sieger[0] = -9;
            }
            else if(equal_players[0] == 1 && equal_players[1] == 3 && equal_players[2] == 4){
                sieger[0] = -10;
            }
            else if(equal_players[0] == 2 && equal_players[1] == 3 && equal_players[2] == 4){
                sieger[0] = -11;
            }
        }
        else if(equal_players.size() == 4){
            if(equal_players[0] == 1 && equal_players[1] == 2 && equal_players[2] == 3 && equal_players[3] == 4){
                sieger[0] = -12;
            }
        }
		return sieger;
	}
	return sieger;
}
void Logic::setAktPlayer(int player){
	this->aktPlayer = player;
}
int Logic::getAktPlayer(){
    return this->aktPlayer;
}

void Logic::setWidth(int i){
    this->width = i;
}

void Logic::setHeight(int i){
    this->height = i;
}

void Logic::setPlayers(int i){
    this->players = i;
}

void Logic::setFields(vector<vector<int> > v){
    this->fields = v;
}

int Logic::getWidth(){
    return this->width;
}

int Logic::getHeight(){
    return this->height;
}

Logic::~Logic() {
	// TODO Auto-generated destructor stub
}

