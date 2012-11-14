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
	Logic var = Logic(8, 8, 4);
	//var.setField(1,1);
	//var.setAktPlayer(2);
	//var.setField(2,2);
	var.setInitStones();

	cout << "Stein laesst sich " << var.validation(3,3) << " setzten (0/nein 1/ja)";

	for(int i = 0; i < var.getFields().size();i++){
		cout << endl;
		for(int j = 0; j < var.getFields()[i].size();j++){
			cout << var.getFields()[i][j] << " ";
		}
	}
	return 0;
}

