#ifndef AI_CODE_H
#define AI_CODE_H
#include "ki_logic.h"

#include <vector>
using namespace std;

class AI_CODE
{
public:
    AI_CODE(int version);
    ki_logic *ai_logic;
    vector<vector<int> > field;
    int version;

    void CODE(vector<vector<int> > field, int *x, int *y, int player);
};

#endif // AI_CODE_H
