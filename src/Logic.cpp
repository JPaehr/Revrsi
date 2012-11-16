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
	this->fields[x][y] = this->aktPlayer;
}
void Logic::setAktPlayer(int player){
	this->aktPlayer = player;
}

Logic::~Logic() {
	// TODO Auto-generated destructor stub
}

