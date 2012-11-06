/*
 * Logic.cpp
 *
 *  Created on: 04.11.2012
 *      Author: jpaehr
 */

#include "Logic.h"
#include <vector>

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
	this->fields(height,vector<int>(width,0));
}
//Array als rueckgabewert einer Methode ist in c schwierig->nachsehen wie das geht
vector<vector<int> > Logic::getFields(){
	return this->fields;
}
void Logic::setInitStones(int players){
	//Fuer 2 Spieler
	if(players == 2){
		//ungerades Spielfeld in der Breite abfragen
		if(this->width % 2 == 0){
			int x = this->width / 2;
		}
		else{
			int x = (this->width / 2) - (1/2);
		}

		//ungerades Spielfeld in der Hoehe
		if(this->height % 2 == 0){
			int y = this->height / 2;
		}
		else{
			int y = (this->height / 2) - (1/2);
		}
	}

	//Fuer 3 Spieler
	if(this->players == 3){
		if(this->width % 2 == 0){
			int x = (this->width / 2) -1;
		}
		else{
			int x = (this->width / 2) - (3/2);
		}
		if(this->height % 2 == 0){
			int y = (this->height / 2) -1;
		}
		else{
			int y = (this->height / 2) - (3/2);
		}
	}

	//Fuer 4 Spieler
	if(this->players == 4){
		if(this->width % 2 == 0){
			int x = (this->width / 2) -2;
		}
		else{
			int x = (this->width / 2) - (3/2);
		}
		if(this->height % 2 == 0){
			int y = (this->height / 2) -2;
		}
		else{
			int y = (this->height / 2) -(3/2);
		}
	}

	//Hier muessen die steine jetzt noch gesetzt werden

}
bool Logic::validation(int x, int y){
	//ist ander Position schon ein stein
	if(this->fields[x][y] == 0){

		//umliegende steine kontrollieren
		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++){
				//wenn i und j beide null muss ausgelassen werden
				if((i != 0 && j != 0) && (x+i >= 0 && x+i <= this->width-1) && (y+j <= this->height-1 && y+j >= 0)){
					return true;
				}
			}
		}
	}

	return false;
}
void Logic::setField(int x, int y){
	this->fields[x][y] = this->aktPlayer;
}

Logic::~Logic() {
	// TODO Auto-generated destructor stub
}

