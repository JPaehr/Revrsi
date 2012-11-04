/*
 * main.cpp
 *
 *  Created on: 04.11.2012
 *      Author: jpaehr
 */

#include <iostream>
#include "Logic.h"




int main(){

	Logic dieLogik(5,5,2);

	dieLogik.setField(3,3);

	std::cout << dieLogik.getFields();// << std::endl;

	return 0;
}

