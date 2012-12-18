#ifndef KI_LOGIC_H
#define KI_LOGIC_H
#include "../Logic.h"

class ki_logic : public Logic
{
public:
    ki_logic(int breite, int hoehe, vector<vector<int> > startvector, int spielerNr);
    void vectorUpdate(vector<vector<int> > aktVector);
    vector<int> KiXY();
    int nr;

};

#endif // KI_LOGIC_H
