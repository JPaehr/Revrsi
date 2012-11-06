/*
 * main.cpp
 *
 *  Created on: 04.11.2012
 *      Author: jpaehr
 */

#include <iostream>
//#include "Logic.h"

using namespace std;


int main(){
	Logic var = Logic(7,9,3);
	for(int i = 0; i < var.getFields().size();i++){
		cout << endl;
		for(int j = 0; j < var.getFields()[i].size();j++){
			cout << var.getFields()[i][j] << " ";
		}
	}
	cout << "tets";
	return 0;
}

