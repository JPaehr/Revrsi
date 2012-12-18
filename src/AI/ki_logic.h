#ifndef KI_LOGIC_H
#define KI_LOGIC_H
#include "../Logic.h"

class ki_logic : public Logic
{
public:
    ki_logic();
    void vectorUpdate(vector<vector<int> > aktVector);
    vector<int> KiXY();
    void setNr(int nr);

private:
    int nr;


};

#endif // KI_LOGIC_H
