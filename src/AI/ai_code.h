#ifndef AI_CODE_H
#define AI_CODE_H

#include <vector>
using namespace std;

class AI_CODE
{
public:
    AI_CODE(int version);
    vector<vector<int> > field;
    int version;

    void CODE(vector<vector<int> > field, int *x, int *y);
};

#endif // AI_CODE_H
