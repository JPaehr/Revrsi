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
}
//Array als rueckgabewert einer Methode ist in c schwierig->nachsehen wie das geht
vector<vector<int> > Logic::getFields(){
	return this->fields;
}
void Logic::setInitStones(){
	int x;
	int y;
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
bool Logic::validation(int x, int y){
	//ist ander Position schon ein stein
	if(this->fields[y][x] == 0){

		//umliegende steine kontrollieren
		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++){
				//wenn i und j beide null muss ausgelassen werden
				if(y+i >= 0 && y+i <= this->height-1 && x+j >= 0 && x+j <= this->width-1 ){
					std::cout << "Breite " << x+j << " Hoehe "<< y+i << " Feld " << this->fields[y+i][x+j] <<  std::endl;
				}

				if(y+i >= 0 && y+i <= this->height-1 && x+j >= 0 && x+j <= this->width-1 && this->fields[y+i][x+j] != 0){
					return true;
				}
			}
		}
	}

	return false;
}
void Logic::setField(int x, int y){
	if(this->validation(x, y)){
		//y und x verdreht, weil y fuer zeilen steht und x fuer breite
		this->fields[y][x] = this->aktPlayer;

		//richtungen legt fest ob in der linie ein gleicher stein gefunden wurde
		// begin oben rechts, also auf eine geraden der steigung 1
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
		for(int k = 1; k <= 8; k++){
			turnStones(x, y, k-1, richtungen[k-1]);
		}

		//neuer Spieler wird gesetzt
		this->aktPlayer = (this->aktPlayer % this->players) + 1;
	}
}
void Logic::setAktPlayer(int player){
	this->aktPlayer = player;
}
int Logic::getAktPlayer(){
	return this->aktPlayer;
}

Logic::~Logic() {
	// TODO Auto-generated destructor stub
}

