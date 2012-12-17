#include "ai_code.h"
#include "ki_logic.h"

AI_CODE::AI_CODE(int version){
    this->version = version;
}

void AI_CODE::CODE(vector<vector<int> > field, int *x, int *y){

    ki_logic ai_logic(field[0].size(), field.size(),3,field, 1);
    (*x) = ai_logic.KiXY()[0];
    (*y) = ai_logic.KiXY()[1];



/*******************  KI  CODE  *******************/

/* Just assign x and y with values
 * like (*x) = 3 and (*y) = 5
 *
*/


}
