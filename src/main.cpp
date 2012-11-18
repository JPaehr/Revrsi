/*
 * main.cpp
 *
 *  Created on: 04.11.2012
 *      Author: jpaehr
 */

#include <iostream>
#include "Logic.h"

using namespace std;


int main(){
	int x, y;
	int breite;
	int hoehe;
	int Spieleranzahl;
	cout << "Spieleranzahl";
	cin >> Spieleranzahl;
	cout << endl << "Breite";
	cin >> breite;
	cout << endl << "Hoehe";
	cin >> hoehe;
	cout << endl;

	Logic var = Logic(breite, hoehe, Spieleranzahl);
	var.setInitStones();
	cout << "Stein laesst sich " << var.validation(3,3) << " setzten (0/nein 1/ja)";
	while(true){

		for(int i = 0; i < var.getFields().size();i++){
			cout << endl;
			for(int j = 0; j < var.getFields()[i].size();j++){
				cout << var.getFields()[i][j] << " ";
			}
		}

		cout << endl << "gib die x Koordinate fuer den neuen Stein ein" << endl;
		cin >> x;
		cout << "gib die y Koordinate fuer den neuen Stein ein" << endl;
		cin >> y;
		var.setField(x, y);
	}
	return 0;
}

