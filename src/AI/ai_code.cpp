#include "ai_code.h"


AI_CODE::AI_CODE(int version){
    this->version = version;
    this->ai_logic = new ki_logic();
}

void AI_CODE::CODE(vector<vector<int> > field, int *x, int *y, int player){
    ai_logic->setNr(player);
    ai_logic->vectorUpdate(field);
    vector<int> rueckgabe = ai_logic->KiXY();
    if(rueckgabe.size() == 0){
        (*x) = -1;
        (*y) = -1;
        return;
    }
    (*x) = rueckgabe[0];
    (*y) = rueckgabe[1];



/*******************  KI  CODE  *******************/

/* Just assign x and y with values
 * like (*x) = 3 and (*y) = 5
 *
*/


}
