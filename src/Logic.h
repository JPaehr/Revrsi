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

public:
	Logic(int width, int height, int players);
	void setInitStones(int players);
	vector<vector<int> > getFields();
	bool validation(int x, int y);
	void setField(int x, int y);
	void setAktPlayer(int player);

	virtual ~Logic();
};

#endif /* LOGIC_H_ */
