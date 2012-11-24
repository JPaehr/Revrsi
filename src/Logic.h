/*
 * Logic.h
 *
 *  Created on: 04.11.2012
 *      Author: jpaehr
 */

#ifndef LOGIC_H_
#define LOGIC_H_
#include <vector>

using namespace std;
class Logic {
private:
	int players;
	int width;
	int height;
	//Leeres array ohne begrenzungen weil konstruktor noch nicht aufgerufen, wahrscheinlich eine schlechte idee
	//gibt auch einen Error beim kompilieren
	vector<vector<int> > fields;//(4,vector<int>(4,0));
	int aktPlayer;
	void turnStones(int x, int y, int richtung, int anzahl);
	bool validation(int x, int y);
	vector<int> sternSteine(int x, int y);

public:
	void setAktPlayer(int player);
	Logic(int width, int height, int players);
	void setInitStones();
	vector<vector<int> > getFields();
	void setField(int x, int y);
	int getAktPlayer();


	virtual ~Logic();
};

#endif /* LOGIC_H_ */
